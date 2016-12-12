#include "client_hf.h"

ssize_t n;
int sockfd;
int TotalNum = 0; //总的空开数量
uint8_t TotalNum_buf[2] = {0};

static uint8_t flag[5] = {0};
static uint8_t buf[N] = {0};
uint8_t getip[16] = {0};
uint8_t* getip_sp = getip;

int getNum(uint8_t* s){
	if(!strcmp(s,"0021")) return 1;
	if(!strcmp(s,"0022")) return 2;
	if(!strcmp(s,"0023")) return 3;
	if(!strcmp(s,"0024")) return 4;
	if(!strcmp(s,"0029")) return 5;
	if(!strcmp(s,"0702")) return 6;
	if(!strcmp(s,"0030")) return 7;   
	return -1;
}

pthread_t thread_reg;
pthread_mutex_t mut_reg;
pthread_mutex_t poll;

void *thread_first(void * arg) {	
//	pthread_mutex_lock(&mut_reg);
	int fd = *((int *)arg);
	uint8_t encryption_buff[N] = {0};
	uint8_t decryption_buff[N] = {0};
	uint8_t send_buf[N] = {0};
	uint8_t sz_buf[N] = {0}; // 2.get time

		pthread_mutex_lock(&mut_reg);
	while((n = read(sockfd, buf, N)) > 0){   
/*			n = recv(sockfd, buf, N, MSG_WAITALL);
		while(1){*/
			printf("read buf: %s\n", buf);
		
			memset(decryption_buff, 0, sizeof(decryption_buff));
			Decryption(buf, decryption_buff);	//解密buf
			memset(buf, 0, sizeof(buf));
			printf("Decryption buf:%d:%s\n",strlen(decryption_buff), decryption_buff);

			if((strlen(decryption_buff)) == 48){
				memcpy(flag, decryption_buff+35, 4);
			}else{
				memcpy(flag, decryption_buff+40, 4);
			}
			
			flag[strlen(flag)] = '\0';
			switch (getNum(flag)) {
				case 1://注册时,接收服务器的消息,get_sz_buffer,"0021"
				
				memcpy(TotalNum_buf, decryption_buff+51, 1);
				TotalNum = atoi((char *)TotalNum_buf);
//				printf("TotalNum:%d\n", TotalNum);
				get_sz_buffer(decryption_buff, sz_buf);

				printf("sz_buf:%s\n", sz_buf);
				add_secret(sz_buf, encryption_buff);
				LOG_PRINT("send buf: %s\n", encryption_buff);

				send(fd, encryption_buff, strlen(encryption_buff)+1, 0);	//发送加密buf
				bzero(encryption_buff, sizeof(encryption_buff));	//清除加密buf
				bzero(sz_buf, sizeof(sz_buf));
				break;
				
				case 2://设置时间时,接收服务器的消息,setTime,"0022"
				setTime(decryption_buff);
				printf("==========End of registration==========\n\n");
				break;
				
				case 3://读取单路空开设备,Read_a_single_device,"0023"
				Read_A_Single_Device(decryption_buff, send_buf);
				
				add_secret(send_buf, encryption_buff);
				send(fd, encryption_buff, strlen(encryption_buff)+1, 0);	//发送加密buf
				bzero(encryption_buff, sizeof(encryption_buff));	//清除加密buf
				bzero(send_buf, sizeof(send_buf));
				break;
				
				case 4://读取全路空开设备,Read_all_device,"0024"
				Read_All_Device(decryption_buff, send_buf);
				
				add_secret(send_buf, encryption_buff);
				send(fd, encryption_buff, strlen(encryption_buff)+1, 0);	//发送加密buf
				bzero(encryption_buff, sizeof(encryption_buff));	//清除加密buf
				bzero(send_buf, sizeof(send_buf));
				break;
				
				case 5://读取单路空开设备,Read_one_device,"0029"
				Read_One_Device(decryption_buff, send_buf);
				
				add_secret(send_buf, encryption_buff);
				send(fd, encryption_buff, strlen(encryption_buff)+1, 0);	//发送加密buf
				bzero(encryption_buff, sizeof(encryption_buff));	//清除加密buf
				bzero(send_buf, sizeof(send_buf));
				break;
				
				case 6://接收服务器心跳包,Heartbeat package,"0702"
				Heartbeat_Package(decryption_buff);
				break;
				
				case 7:	//"0030"
				break_brake(decryption_buff, send_buf);
				
				add_secret(send_buf, encryption_buff);
				send(fd, encryption_buff, strlen(encryption_buff)+1, 0);	//发送加密buf
				bzero(encryption_buff, sizeof(encryption_buff));	//清除加密buf
				bzero(send_buf, sizeof(send_buf));
				break;

			default:
				break;
			}
		}
		pthread_mutex_unlock(&mut_reg);
	pthread_exit(NULL);
}

int main(int argc, const char *argv[]) {
	int temp;
	uint8_t encryption_buff[N] = {0};
	uint8_t decryption_buff[N] = {0};
	uint8_t* zc_buf_sp = NULL; // 1.registered
	struct sockaddr_in servaddr;
	uint8_t Mac[17] = {0};
	uint8_t buf2[256] = {0};
	int i = 0, nbyte;
	
	int nRtn = get_mac(Mac, sizeof(Mac));  //获取Mac地址
	LOG_PRINT("Mac: %s\n", Mac);
	
	do {
		getip_sp = (uint8_t *)GetLocalIp(); //获取IP地址
		if(!(strcmp("192.168.1.233", getip_sp))) {
			printf("getIp failed; retry times %d\n", i);
			i++;
			if(i == 6)system("udhcpc");
			sleep(1);
		} else {
			LOG_PRINT("Get IP succeed:%s\n\n", getip_sp);
		}
	} while(!(strcmp("192.168.1.233", getip_sp)));
	
	printf("==========Start of registration==========\n");
	
	zc_buf_sp = (uint8_t *)get_zc_buffer(Mac);
	LOG_PRINT("zc_buf: %s\n", zc_buf_sp);

	add_secret(zc_buf_sp, encryption_buff);  //加密处理
	LOG_PRINT("send buf: %s\n", encryption_buff);

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket to fail\n");
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("210.72.224.35");
	servaddr.sin_port = htons(8502);

	if((connect(sockfd, (struct sockaddr *)(&servaddr), sizeof(servaddr))) == -1) {
		perror("connect to fail\n");
		exit(0);
	}else{
		printf("connect server succeed!...\n");
	}


	memset(&thread_reg, 0, sizeof(thread_reg));	
	pthread_mutex_init(&mut_reg, NULL);
	pthread_mutex_init(&poll, NULL);

	if((temp = pthread_create(&thread_reg, NULL, thread_first, (int *)&sockfd)) != 0) {
		printf("thread_reg to failed\n");		
		exit(0);	
	}
	sleep(1);
	if((send(sockfd, encryption_buff, strlen(encryption_buff)+1, 0)) == -1) { //发送加密data
		LOG_PRINT("send to failed\n");
		exit(1);
	}else
	bzero(encryption_buff, sizeof(encryption_buff));	//清除加密data

	sleep(2);
//	pthread_mutex_lock(&poll);
	Gateway_Poll();
///	pthread_mutex_unlock(&poll);
	
	pthread_join(thread_reg, NULL);
	close(sockfd);

	return 0;;
}

