#include "com_RW.h"
#include "print.h"
#define READ_SIZE 30

struct _cmd {
	uint8_t sendData_1[8];
	uint8_t sendData_2[8];
	uint8_t sendData_3[8];
	uint8_t sendData_4[8];
	uint8_t sendData_5[8];
	uint8_t sendData_6[8];
} cmd = {
	{0x01, 0x04, 0x00, 0x10, 0x00, 0x0C, 0xF1, 0xCA}, {0x02, 0x04, 0x00, 0x10, 0x00, 0x0C, 0xF1, 0xF9},\
	{0x03, 0x04, 0x00, 0x10, 0x00, 0x0C, 0xF0 ,0x28}, {0x04, 0x04, 0x00, 0x10, 0x00, 0x0C, 0xF1, 0x9F},\
	{0x04, 0x04, 0x00, 0x10, 0x00, 0x0C, 0xF0 ,0x4E}, {0x04, 0x04, 0x00, 0x10, 0x00, 0x0C, 0xF0, 0x7D},
};
int g_fd;
extern int TotalNum;
extern int sockfd;
static int times = 0, heart = 0;
double Current = 0.0; //??????÷
double Voltage = 0.0; //????????
double Active_power = 0.0;	//????????????????
double Electricity_Quantity = 0.0;	//????????
int Fault_type = 0;	//??í??ó??à????/×??????×??
uint32_t Leakage_current = 0; //??????????????÷
uint32_t Temperature = 0; //????????

double Current_01 = 0.0;
double Voltage_01 = 0.0;
double Active_power_01 = 0.0;
double Electricity_Quantity_01 = 0.0;
int Fault_type_01 = 0;
uint32_t Leakage_current_01 = 0;
uint32_t Temperature_01 = 0;

double Current_02 = 0.0;
double Voltage_02 = 0.0;
double Active_power_02 = 0.0;
double Electricity_Quantity_02 = 0.0;
int Fault_type_02 = 0;
uint32_t Leakage_current_02 = 0;
uint32_t Temperature_02 = 0;

double Current_03 = 0.0;
double Voltage_03 = 0.0;
double Active_power_03 = 0.0;
double Electricity_Quantity_03 = 0.0;
int Fault_type_03 = 0;
uint32_t Leakage_current_03 = 0;
uint32_t Temperature_03 = 0;

double Current_04 = 0.0;
double Voltage_04 = 0.0;
double Active_power_04 = 0.0;
double Electricity_Quantity_04 = 0.0;
int Fault_type_04 = 0;
uint32_t Leakage_current_04 = 0;
uint32_t Temperature_04 = 0;

double Current_05 = 0.0;
double Voltage_05 = 0.0;
double Active_power_05 = 0.0;
double Electricity_Quantity_05 = 0.0;
int Fault_type_05 = 0;
uint32_t Leakage_current_05 = 0;
uint32_t Temperature_05 = 0;

double Current_06 = 0.0;
double Voltage_06 = 0.0;
double Active_power_06 = 0.0;
double Electricity_Quantity_06 = 0.0;
int Fault_type_06 = 0;
uint32_t Leakage_current_06 = 0;
uint32_t Temperature_06 = 0;
#if 1
long int i_01 = 0, i_02 = 0, i_03 = 0, i_04 = 0, i_05 = 0, i_06 = 0;
double upload_Current_01 = 0.0;
double upload_Voltage_01 = 0.0;
double upload_Active_power_01 = 0.0;
double upload_Electricity_Quantity_01 = 0.0;
uint32_t upload_Leakage_current_01 = 0;
uint32_t upload_Temperature_01 = 0;
uint8_t upload_Current_01_buf[8] = {0};
uint8_t upload_Voltage_01_buf[8] = {0};
uint8_t upload_Active_power_01_buf[8] = {0};
uint8_t upload_Electricity_Quantity_01_buf[8] = {0};
uint8_t upload_Leakage_current_01_buf[8] = {0};
uint8_t upload_Temperature_01_buf[8] = {0};
uint8_t Fault_type_01_buf[5] = {0};

double upload_Current_02 = 0.0;
double upload_Voltage_02 = 0.0;
double upload_Active_power_02 = 0.0;
double upload_Electricity_Quantity_02 = 0.0;
uint32_t upload_Leakage_current_02 = 0;
uint32_t upload_Temperature_02 = 0;
uint8_t upload_Current_02_buf[8] = {0};
uint8_t upload_Voltage_02_buf[8] = {0};
uint8_t upload_Active_power_02_buf[8] = {0};
uint8_t upload_Electricity_Quantity_02_buf[8] = {0};
uint8_t upload_Leakage_current_02_buf[8] = {0};
uint8_t upload_Temperature_02_buf[8] = {0};
uint8_t Fault_type_02_buf[5] = {0};

double upload_Current_03 = 0.0;
double upload_Voltage_03 = 0.0;
double upload_Active_power_03 = 0.0;
double upload_Electricity_Quantity_03 = 0.0;
uint32_t upload_Leakage_current_03 = 0;
uint32_t upload_Temperature_03 = 0;
uint8_t upload_Current_03_buf[8] = {0};
uint8_t upload_Voltage_03_buf[8] = {0};
uint8_t upload_Active_power_03_buf[8] = {0};
uint8_t upload_Electricity_Quantity_03_buf[8] = {0};
uint8_t upload_Leakage_current_03_buf[8] = {0};
uint8_t upload_Temperature_03_buf[8] = {0};
uint8_t Fault_type_03_buf[5] = {0};

double upload_Current_04 = 0.0;
double upload_Voltage_04 = 0.0;
double upload_Active_power_04 = 0.0;
double upload_Electricity_Quantity_04 = 0.0;
uint32_t upload_Leakage_current_04 = 0;
uint32_t upload_Temperature_04 = 0;
uint8_t upload_Current_04_buf[8] = {0};
uint8_t upload_Voltage_04_buf[8] = {0};
uint8_t upload_Active_power_04_buf[8] = {0};
uint8_t upload_Electricity_Quantity_04_buf[8] = {0};
uint8_t upload_Leakage_current_04_buf[8] = {0};
uint8_t upload_Temperature_04_buf[8] = {0};
uint8_t Fault_type_04_buf[5] = {0};

double upload_Current_05 = 0.0;
double upload_Voltage_05 = 0.0;
double upload_Active_power_05 = 0.0;
double upload_Electricity_Quantity_05 = 0.0;
uint32_t upload_Leakage_current_05 = 0;
uint32_t upload_Temperature_05 = 0;
uint8_t upload_Current_05_buf[8] = {0};
uint8_t upload_Voltage_05_buf[8] = {0};
uint8_t upload_Active_power_05_buf[8] = {0};
uint8_t upload_Electricity_Quantity_05_buf[8] = {0};
uint8_t upload_Leakage_current_05_buf[8] = {0};
uint8_t upload_Temperature_05_buf[8] = {0};
uint8_t Fault_type_05_buf[5] = {0};

double upload_Current_06 = 0.0;
double upload_Voltage_06 = 0.0;
double upload_Active_power_06 = 0.0;
double upload_Electricity_Quantity_06 = 0.0;
uint32_t upload_Leakage_current_06 = 0;
uint32_t upload_Temperature_06 = 0;
uint8_t upload_Current_06_buf[8] = {0};
uint8_t upload_Voltage_06_buf[8] = {0};
uint8_t upload_Active_power_06_buf[8] = {0};
uint8_t upload_Electricity_Quantity_06_buf[8] = {0};
uint8_t upload_Leakage_current_06_buf[8] = {0};
uint8_t upload_Temperature_06_buf[8] = {0};
uint8_t Fault_type_06_buf[5] = {0};

uint8_t auto_upload_All_meg[M] = {0};
uint8_t encryption_auto_upload_All_meg[M] = {0};
uint8_t Stamp[12] = {0};
#endif

void flo_to_str(double a, uint8_t* buf, int i) { //i为小数点后需要保留的位数

	char str[50] = {0};
	char ch = '.';
	char *pt;
	sprintf(str, "%lf", a);
	pt = strchr(str, ch);
	int b;
	b = pt - str;
	memcpy(buf, str, (b+i+1));
	buf[strlen((char *)buf)] = '\0';
}

void flo_to_str_V(double a, uint8_t* buf, int i) { //i为小数点后需要保留的位数

	char str[50] = {0};
	char ch = '.';
	char *pt;
	sprintf(str, "%lf", a);
	pt = strchr(str, ch);
	int b;
	b = pt - str;
	if(b == 1){
		memcpy(buf, "00", 2);
		memcpy(buf+2, str, (b+i+1));
	}else if(b == 2){
		memcpy(buf, "0", 1);
		memcpy(buf+1, str, (b+i+1));
	}else if(b == 3){
		memcpy(buf, str, (b+i+1));
	}
	buf[strlen((char *)buf)] = '\0';
}


void send_ci_buffer(void) {
	uint8_t Mac[12] = {0};
	get_mac(Mac, sizeof(Mac));
	uint8_t ci_buf[N] = {0}; // download
	uint8_t encryption_ci_buf[N] = {0};
	strcat(ci_buf, "#ci#0101#");
	strcat(ci_buf, Mac);
	strcat(ci_buf, "#0023#7.1.1#000000#0701#0000;0000;0000#");

	ci_buf[strlen(ci_buf)] = '\0';
	printf("ci_buf:%s\n", ci_buf);
	add_secret(ci_buf, encryption_ci_buf);
	send(sockfd, encryption_ci_buf, strlen(encryption_ci_buf)+1, 0);	//发送加密buf
	bzero(encryption_ci_buf, sizeof(encryption_ci_buf));	//清除加密buf
}


void getTimestamp(uint8_t* stamp) {
	int ii = 0;
	time_t t;
	t = time(NULL);
	ii = time(&t);
	sprintf(stamp, "%d", ii);
	printf("stamp:%s\n", stamp);
}

void break_brake(uint8_t *buffer, uint8_t *Break_Brake) {
	int a;
	uint8_t	which_switch[5] = {0};
	memcpy(which_switch, buffer+45, 2);
	which_switch[strlen(which_switch)] = '\0';
	uint8_t Encryption_Break_Brake[N] = {0};

	switch(getnum(which_switch)) {
	case 1: {
		uint8_t Break[10] = {0x01, 0x06, 0x01, 0xD0, 0x00, 0x01, 0x48, 0x0F};
		a = write(g_fd, Break, 8);
		if(a > 0) {
			strcat(Break_Brake, "#rs#");
			strcat(Break_Brake, buffer);
			Break_Brake[strlen(Break_Brake)] = '\0';
		}
		break;
	}
	case 2: {
		uint8_t Break[10] = {0x02, 0x06, 0x01, 0xD0, 0x00, 0x01, 0x48, 0x3C};
		a = write(g_fd, Break, 8);
		if(a > 0) {
			strcat(Break_Brake, "#rs#");
			strcat(Break_Brake, buffer);
			Break_Brake[strlen(Break_Brake)] = '\0';
		}
		break;
	}
	case 3: {
		uint8_t Break[10] = {0x03, 0x06, 0x01, 0xD0, 0x00, 0x01, 0x49, 0xED};
		a = write(g_fd, Break, 8);
		if(a > 0) {
			strcat(Break_Brake, "#rs#");
			strcat(Break_Brake, buffer);
			Break_Brake[strlen(Break_Brake)] = '\0';
		}
		break;
	}
	case 4: {
		uint8_t Break[10] = {0x04, 0x06, 0x01, 0xD0, 0x00, 0x01, 0x48, 0x5A};
		a = write(g_fd, Break, 8);
		if(a > 0) {
			strcat(Break_Brake, "#rs#");
			strcat(Break_Brake, buffer);
			Break_Brake[strlen(Break_Brake)] = '\0';
		}
		break;
	}
	case 5: {
		uint8_t Break[10] = {0x04, 0x06, 0x01, 0xD0, 0x00, 0x01, 0x49, 0x8B};
		a = write(g_fd, Break, 8);
		if(a > 0) {
			strcat(Break_Brake, "#rs#");
			strcat(Break_Brake, buffer);
			Break_Brake[strlen(Break_Brake)] = '\0';
		}
		break;
	}
	case 6: {
		uint8_t Break[10] = {0x04, 0x06, 0x01, 0xD0, 0x00, 0x01, 0x49, 0xB8};
		a = write(g_fd, Break, 8);
		if(a > 0) {
			strcat(Break_Brake, "#rs#");
			strcat(Break_Brake, buffer);
			Break_Brake[strlen(Break_Brake)] = '\0';
		}
		break;
	}
	}


}


void myDelay(int delay) {
	if(delay <= 0)
		return;
	struct timeval timeout;
#if 0
	timeout.tv_sec = delay/1000;
	timeout.tv_usec = (delay % 1000) * 1000000;
#endif
	timeout.tv_sec = delay/1000;
	timeout.tv_usec = 0;
	select(1, 0, NULL, NULL, &timeout);
}

int sendCmdToSerial() {

	unsigned char *cmd_sp;
	cmd_sp = (unsigned char *)&cmd;
	int ret = -1, i, j;
	static char g_writeBuff[8] = {0};
	static struct timeval lastSendTime= {0,0};
	struct timeval l_tv;

	if(-1==gettimeofday(&l_tv, NULL)) {
		printf("sendCmdToSerial():fail to get time\n");
		return -1;
	}
	unsigned long elapseTime=(l_tv.tv_sec-lastSendTime.tv_sec)*1000000+(l_tv.tv_usec-lastSendTime.tv_usec);///us

	if(elapseTime< SEND_SERIAL_INTERVAL) {
		myDelay((int)((SEND_SERIAL_INTERVAL-elapseTime)/1000));
	}

	if(-1==gettimeofday(&lastSendTime, NULL)) {
		printf("sendCmdToSerial():fail to get time\n");
		return -1;
	}

	while(1) {

		for(j = 0; j < TotalNum; j++) {
			memcpy(g_writeBuff, cmd_sp+(j*8), 8);
			ret = write(g_fd, g_writeBuff, 8);
			usleep(1);
			printf("-----------------  write content begin -----------------%d\n", times);
			printf("Write %d Byte Data is: ", ret);
			for(i=0; i<8; i++) {
				printf("%02x ", g_writeBuff[i]);
			}
			printf("\n-----------------  write content  end  ----------------- \n");

			times++;
//			printf("%d %d %d %d %d %d\n", i_01, i_02, i_03, i_04, i_05, i_06);
			if(times > 200){
				times = 0;
//				i_01 = 0;i_02 = 0;i_03 = 0;i_04 = 0;i_05 = 0;i_06 = 0;
			}
			if(-1 == ret) {
				printf("write fialed\n");
				tcflush(g_fd, TCOFLUSH);
			}
			memset(g_writeBuff, 0, 8);
			sleep(1);
		}
	}
	return 0;
}

int readcom() {
	int ret, len, read_2_len;
	fd_set rfds;
	unsigned char buf[30] = {0};
	unsigned char buf_all[30] = {0};
	unsigned char *p_buf = buf;
	struct timeval tmout;
	int i, j = 0;
	for(;;) {
		FD_ZERO(&rfds);
		FD_SET(g_fd,&rfds);
		tmout.tv_sec = 1;
		tmout.tv_usec = 0;

		ret = select(g_fd+1, &rfds, NULL, NULL, &tmout);
		if(ret < 0) {
			printf("ret = %d\n", ret);
			break;
		} else if(ret == 0) {
			continue;
		} else {
			if(FD_ISSET(g_fd,&rfds)) {

				len = read(g_fd, buf, READ_SIZE);
				usleep(1);
#if 1
				memcpy(buf_all+j, buf, len);
				j += len;
				if(j >= 29) {
					printf("-----------------  read content begin  -----------------\n");
					printf("Read %d Byte Data is: ", j);
					for(i = 0; i < j; i++)	printf("%02x ",buf_all[i]); //fflush(stdout);
					printf("\n-----------------  read content  end   -----------------\n");
					analysis_Data(buf_all);
					memset(buf_all, 0, sizeof(buf_all));
					j = 0;
				} else {
					continue;
				}

#endif
				memset(buf, 0, sizeof(buf));
			} else 	{
				printf("FD_ISSET_read wrong\n");
				continue;
			}
		}
	}
	return len;
}


uint32_t htoi(char *s) {
	uint32_t n = 0;
	uint32_t i = 0;
	while(s[i] != '\0' && s[i] != '\n') {
		if(s[i] == '0') {
			if(s[i+1] == 'x' || s[i+1] == 'X')
				i+=2;
		}
		if(s[i] >= '0' && s[i] <= '9') {
			n = n * 16 + (s[i] - '0');
		} else if(s[i] >= 'a' && s[i] <= 'f') {
			n = n * 16 + (s[i] - 'a') + 10;
		} else if(s[i] >= 'A' && s[i] <= 'F') {
			n = n * 16 + (s[i] - 'A') + 10;
		} else
			return -1;
		++i;
	}
	return n;
}

float Hex_To_Decimal(unsigned char *Byte) {
	return *((float*)Byte);
}

void analysis_Data(unsigned char *buf) {
	uint8_t Current_buf[4] = {0};
	uint8_t	Voltage_buf[4] = {0};
	uint8_t	Active_power_buf[4] = {0};
	uint8_t	Leakage_current_buf[4] = {0};
	uint8_t Temperature_buf[4] = {0};
	uint8_t	Electricity_Quantity_buf[4] = {0};
	uint8_t buf_1[2] = {0};
	uint8_t buf_2[2] = {0};
	uint8_t buf_first[2] = {0};
	uint8_t *buf_sp = buf;
	uint8_t abnormal[N] = {0};
	uint8_t encryption_abnormal[N] = {0};
	uint8_t Mac[17] = {0};
	uint8_t stamp[12] = {0};

	Current_buf[0] = *(buf_sp+6); //计算电流
	Current_buf[1] = *(buf_sp+5);
	Current_buf[2] = *(buf_sp+4);
	Current_buf[3] = *(buf_sp+3);

	buf_1[0] = *(buf_sp+7); //计算漏电电流
	buf_1[1] = *(buf_sp+8);
	sprintf(Leakage_current_buf, "%02x", buf_1[0]);
	sprintf(Leakage_current_buf+2, "%02x", buf_1[1]);

	Voltage_buf[0] = *(buf_sp+12); //计算电压
	Voltage_buf[1] = *(buf_sp+11);
	Voltage_buf[2] = *(buf_sp+10);
	Voltage_buf[3] = *(buf_sp+9);

	buf_2[0] = *(buf_sp+13); //计算温度
	buf_2[1] = *(buf_sp+14);
	sprintf(Temperature_buf, "%02x", buf_2[0]);
	sprintf(Temperature_buf+2, "%02x", buf_2[1]);

	Active_power_buf[0]	= *(buf_sp+18);  //计算有功功率
	Active_power_buf[1]	= *(buf_sp+17);
	Active_power_buf[2]	= *(buf_sp+16);
	Active_power_buf[3]	= *(buf_sp+15);

	Electricity_Quantity_buf[0] = *(buf_sp+22);  //计算电量
	Electricity_Quantity_buf[1] = *(buf_sp+21);
	Electricity_Quantity_buf[2] = *(buf_sp+20);
	Electricity_Quantity_buf[3] = *(buf_sp+19);

	Current = Hex_To_Decimal(Current_buf);
	Voltage = Hex_To_Decimal(Voltage_buf);
	Active_power = Hex_To_Decimal(Active_power_buf);
	Leakage_current = htoi(Leakage_current_buf)/10;
	Temperature = htoi(Temperature_buf)/10;
	Electricity_Quantity = Hex_To_Decimal(Electricity_Quantity_buf);

	printf("I = %0.3fA; V = %0.3fV; P = %0.3fW; L_I = %dmA; T = %d`C; Q = %0.4fkwh; ",\
	       Current, Voltage, Active_power, Leakage_current, Temperature, Electricity_Quantity);

	switch (buf[26]) { //判断错误类型
	case 0x00:
		Fault_type = 0x00;
		printf("Fault_type: NO Fault!\n\n");
		break;
	case 0x01:
		Fault_type = 0x10;
		printf("Fault_type: Overload!\n\n");
		sprintf(buf_first, "%02d", buf[0]);
		get_mac(Mac, sizeof(Mac));
		get_stamp(stamp);
		strcat(abnormal, "#rz#0101#");
		strcat(abnormal, Mac);
		strcat(abnormal, "#00SB#7.1.1#000000#0027#");
		strcat(abnormal, buf_first);
		strcat(abnormal, ";");
		strcat(abnormal, stamp);
		strcat(abnormal, ";");
		strcat(abnormal, "01#");
		abnormal[strlen(abnormal)] = '\0';
		printf("send buf:%s\n", abnormal);
		add_secret(abnormal, encryption_abnormal);
		if((send(sockfd, encryption_abnormal, strlen(encryption_abnormal)+1, 0)) == -1) { //发送加密data
			LOG_PRINT("send to failed\n");
			exit(1);
		}
		bzero(encryption_abnormal, sizeof(encryption_abnormal));	//清除加密data
		bzero(abnormal, sizeof(abnormal));
		break;
	case 0x02:
		Fault_type = 0x20;
		printf("Fault_type: Short Circuit!\n\n");
		sprintf(buf_first, "%02d", buf[0]);
		get_mac(Mac, sizeof(Mac));
		get_stamp(stamp);
		strcat(abnormal, "#rz#0101#");
		strcat(abnormal, Mac);
		strcat(abnormal, "#00SB#7.1.1#000000#0027#");
		strcat(abnormal, buf_first);
		strcat(abnormal, ";");
		strcat(abnormal, stamp);
		strcat(abnormal, ";");
		strcat(abnormal, "20#");

		abnormal[strlen(abnormal)] = '\0';
		printf("send buf:%s\n", abnormal);
		add_secret(abnormal, encryption_abnormal);
		if((send(sockfd, encryption_abnormal, strlen(encryption_abnormal)+1, 0)) == -1) { //发送加密data
			LOG_PRINT("send to failed\n");
			exit(1);
		}
		bzero(encryption_abnormal, sizeof(encryption_abnormal));	//清除加密data
		bzero(abnormal, sizeof(abnormal));
		break;

	case 0x04:
		Fault_type = 0x08;
		printf("Fault_type: Leakage!\n\n");
		sprintf(buf_first, "%02d", buf[0]);
		get_mac(Mac, sizeof(Mac));
		get_stamp(stamp);
		strcat(abnormal, "#rz#0101#");
		strcat(abnormal, Mac);
		strcat(abnormal, "#00SB#7.1.1#000000#0027#");
		strcat(abnormal, buf_first);
		strcat(abnormal, ";");
		strcat(abnormal, stamp);
		strcat(abnormal, ";");
		strcat(abnormal, "04#");
		abnormal[strlen(abnormal)] = '\0';
		printf("send buf:%s\n", abnormal);
		add_secret(abnormal, encryption_abnormal);
		if((send(sockfd, encryption_abnormal, strlen(encryption_abnormal)+1, 0)) == -1) { //发送加密data
			LOG_PRINT("send to failed\n");
			exit(1);
		}
		bzero(encryption_abnormal, sizeof(encryption_abnormal));	//清除加密data
		bzero(abnormal, sizeof(abnormal));
		break;

	case 0x08:
		Fault_type = 0x80;
		printf("Fault_type: Under Voltage!\n\n");
		sprintf(buf_first, "%02d", buf[0]);
		get_mac(Mac, sizeof(Mac));
		get_stamp(stamp);
		strcat(abnormal, "#rz#0101#");
		strcat(abnormal, Mac);
		strcat(abnormal, "#00SB#7.1.1#000000#0027#");
		strcat(abnormal, buf_first);
		strcat(abnormal, ";");
		strcat(abnormal, stamp);
		strcat(abnormal, ";");
		strcat(abnormal, "08#");
		abnormal[strlen(abnormal)] = '\0';
		printf("send buf:%s\n", abnormal);
		add_secret(abnormal, encryption_abnormal);
		if((send(sockfd, encryption_abnormal, strlen(encryption_abnormal)+1, 0)) == -1) { //发送加密data
			LOG_PRINT("send to failed\n");
			exit(1);
		}
		bzero(encryption_abnormal, sizeof(encryption_abnormal));	//清除加密data
		bzero(abnormal, sizeof(abnormal));
		break;

	case 0x10:
		Fault_type = 0x40;
		printf("Fault_type: Over Voltage!\n\n");
		sprintf(buf_first, "%02d", buf[0]);
		get_mac(Mac, sizeof(Mac));
		get_stamp(stamp);
		strcat(abnormal, "#rz#0101#");
		strcat(abnormal, Mac);
		strcat(abnormal, "#00SB#7.1.1#000000#0027#");
		strcat(abnormal, buf_first);
		strcat(abnormal, ";");
		strcat(abnormal, stamp);
		strcat(abnormal, ";");
		strcat(abnormal, "10#");
		abnormal[strlen(abnormal)] = '\0';
		printf("send buf:%s\n", abnormal);
		add_secret(abnormal, encryption_abnormal);
		if((send(sockfd, encryption_abnormal, strlen(encryption_abnormal)+1, 0)) == -1) { //发送加密data
			LOG_PRINT("send to failed\n");
			exit(1);
		}
		bzero(encryption_abnormal, sizeof(encryption_abnormal));	//清除加密data
		bzero(abnormal, sizeof(abnormal));
		break;

	default:
		printf("error\n");
		break;
	}

	switch (buf[0]) {
	case 0x01:
		Current_01 = Current;
		Voltage_01 = Voltage;
		Active_power_01 = Active_power;
		Electricity_Quantity_01 = Electricity_Quantity;
		Leakage_current_01 = Leakage_current;
		Temperature_01 = Temperature;
		Fault_type_01 = Fault_type;
#if 1
		upload_Current_01 += Current;
		upload_Voltage_01 += Voltage;
		upload_Active_power_01 += Active_power;
		upload_Electricity_Quantity_01 += Electricity_Quantity;
		upload_Leakage_current_01 += Leakage_current;
		upload_Temperature_01 += Temperature;
		++i_01;
#endif

		break;

	case 0x02:
		Current_02 = Current;
		Voltage_02 = Voltage;
		Active_power_02 = Active_power;
		Electricity_Quantity_02 = Electricity_Quantity;
		Leakage_current_02 = Leakage_current;
		Temperature_02 = Temperature;
		Fault_type_02 = Fault_type;
#if 1
		upload_Current_02 += Current;
		upload_Voltage_02 += Voltage;
		upload_Active_power_02 += Active_power;
		upload_Electricity_Quantity_02 += Electricity_Quantity;
		upload_Leakage_current_02 += Leakage_current;
		upload_Temperature_02 += Temperature;
		++i_02;
#endif

		break;

	case 0x03:
		Current_03 = Current;
		Voltage_03 = Voltage;
		Active_power_03 = Active_power;
		Electricity_Quantity_03 = Electricity_Quantity;
		Leakage_current_03 = Leakage_current;
		Temperature_03 = Temperature;
		Fault_type_03 = Fault_type;
#if 1
		upload_Current_03 += Current;
		upload_Voltage_03 += Voltage;
		upload_Active_power_03 += Active_power;
		upload_Electricity_Quantity_03 += Electricity_Quantity;
		upload_Leakage_current_03 += Leakage_current;
		upload_Temperature_03 += Temperature;
		++i_03;
#endif
		break;

	case 0x04:
		Current_04 = Current;
		Voltage_04 = Voltage;
		Active_power_04 = Active_power;
		Electricity_Quantity_04 = Electricity_Quantity;
		Leakage_current_04 = Leakage_current;
		Temperature_04 = Temperature;
		Fault_type_04 = Fault_type;
#if 1
		upload_Current_04 += Current;
		upload_Voltage_04 += Voltage;
		upload_Active_power_04 += Active_power;
		upload_Electricity_Quantity_04 += Electricity_Quantity;
		upload_Leakage_current_04 += Leakage_current;
		upload_Temperature_04 += Temperature;
		++i_04;
#endif

		break;

	case 0x05:
		Current_05 = Current;
		Voltage_05 = Voltage;
		Active_power_05 = Active_power;
		Electricity_Quantity_05 = Electricity_Quantity;
		Leakage_current_05 = Leakage_current;
		Temperature_05 = Temperature;
		Fault_type_05 = Fault_type;
#if 1
		upload_Current_05 += Current;
		upload_Voltage_05 += Voltage;
		upload_Active_power_05 += Active_power;
		upload_Electricity_Quantity_05 += Electricity_Quantity;
		upload_Leakage_current_05 += Leakage_current;
		upload_Temperature_05 += Temperature;
		++i_05;
#endif
		break;

	case 0x06:
		Current_06 = Current;
		Voltage_06 = Voltage;
		Active_power_06 = Active_power;
		Electricity_Quantity_06 = Electricity_Quantity;
		Leakage_current_06 = Leakage_current;
		Temperature_06 = Temperature;
		Fault_type_06 = Fault_type;
#if 1
		upload_Current_06 += Current;
		upload_Voltage_06 += Voltage;
		upload_Active_power_06 += Active_power;
		upload_Electricity_Quantity_06 += Electricity_Quantity;
		upload_Leakage_current_06 += Leakage_current;
		upload_Temperature_06 += Temperature;
		++i_06;
#endif
		break;

	default:
		break;
	}
#if 1
	if((times == 5) || (times == 105)) {
		printf("--------- Heartbeat Package Asked Start ----------\n");
		send_ci_buffer();
	}
	if(times == 200) {
		if(TotalNum == 1) {
			flo_to_str(upload_Current_01/(i_01*1.0), upload_Current_01_buf, 3);
			flo_to_str_V(upload_Voltage_01/(i_01*1.0), upload_Voltage_01_buf, 1);
			flo_to_str(upload_Active_power_01/(i_01*1000.0), upload_Active_power_01_buf, 4);
			flo_to_str(upload_Electricity_Quantity_01/(i_01*1.0), upload_Electricity_Quantity_01_buf, 2);
			sprintf(upload_Leakage_current_01_buf, "%d", upload_Leakage_current_01/i_01);
			sprintf(upload_Temperature_01_buf, "%02d", upload_Temperature_01/i_01);
			sprintf(Fault_type_01_buf, "%02d", Fault_type_01);

			get_mac(Mac, sizeof(Mac));
			getTimestamp(Stamp);
			strcat(auto_upload_All_meg, "#cc#0101#");
			strcat(auto_upload_All_meg, Mac);
			strcat(auto_upload_All_meg, "#00SB#7.1.1#000000#0028#01#");
			strcat(auto_upload_All_meg, Stamp);

			strcat(auto_upload_All_meg, "#01;");
			strcat(auto_upload_All_meg, upload_Voltage_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_01_buf);
			strcat(auto_upload_All_meg, "#");

			auto_upload_All_meg[strlen(auto_upload_All_meg)] = '\0';
			printf("auto_upload_All_meg:%s\n", auto_upload_All_meg);
			add_secret(auto_upload_All_meg, encryption_auto_upload_All_meg);
			if((send(sockfd, encryption_auto_upload_All_meg, strlen(encryption_auto_upload_All_meg)+1, 0)) == -1) {	//发送加密buf
				printf("send failed\n");
				exit(1);
			} else {
				printf("send succeed\n\n");
			}
			memset(encryption_auto_upload_All_meg, 0,  sizeof(encryption_auto_upload_All_meg));	//清除加密buf
			memset(auto_upload_All_meg, 0, sizeof(auto_upload_All_meg));

			i_01 = 0;
			upload_Current_01 = 0;
			upload_Voltage_01 = 0;
			upload_Active_power_01 = 0;
			upload_Electricity_Quantity_01 = 0;
			upload_Leakage_current_01 = 0;
			upload_Temperature_01 = 0;
		}
		if(TotalNum == 2) {
			flo_to_str(upload_Current_01/(i_01*1.0), upload_Current_01_buf, 3);
			flo_to_str_V(upload_Voltage_01/(i_01*1.0), upload_Voltage_01_buf, 1);
			flo_to_str(upload_Active_power_01/(i_01*1000.0), upload_Active_power_01_buf, 4);
			flo_to_str(upload_Electricity_Quantity_01/(i_01*1.0), upload_Electricity_Quantity_01_buf, 2);
			sprintf(upload_Leakage_current_01_buf, "%d", upload_Leakage_current_01/i_01);
			sprintf(upload_Temperature_01_buf, "%02d", upload_Temperature_01/i_01);
			sprintf(Fault_type_01_buf, "%02d", Fault_type_01);

			flo_to_str(upload_Current_02/(i_02*1.0), upload_Current_02_buf, 3);
			flo_to_str_V(upload_Voltage_02/(i_02*1.0), upload_Voltage_02_buf, 1);
			flo_to_str(upload_Active_power_02/(i_02*1000.0), upload_Active_power_02_buf, 4);
			flo_to_str(upload_Electricity_Quantity_02/(i_02*1.0), upload_Electricity_Quantity_02_buf, 2);
			sprintf(upload_Leakage_current_02_buf, "%d", upload_Leakage_current_02/i_02);
			sprintf(upload_Temperature_02_buf, "%02d", upload_Temperature_02/i_02);
			sprintf(Fault_type_02_buf, "%02d", Fault_type_02);

			get_mac(Mac, sizeof(Mac));
			getTimestamp(Stamp);
			strcat(auto_upload_All_meg, "#cc#0101#");
			strcat(auto_upload_All_meg, Mac);
			strcat(auto_upload_All_meg, "#00SB#7.1.1#000000#0028#02#");
			strcat(auto_upload_All_meg, Stamp);

			strcat(auto_upload_All_meg, "#01;");
			strcat(auto_upload_All_meg, upload_Voltage_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_01_buf);

			strcat(auto_upload_All_meg, "#02;");
			strcat(auto_upload_All_meg, upload_Voltage_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_02_buf);
			strcat(auto_upload_All_meg, "#");

			auto_upload_All_meg[strlen(auto_upload_All_meg)] = '\0';
			printf("auto_upload_All_meg:%s\n", auto_upload_All_meg);
			add_secret(auto_upload_All_meg, encryption_auto_upload_All_meg);
			if((send(sockfd, encryption_auto_upload_All_meg, strlen(encryption_auto_upload_All_meg)+1, 0)) == -1) {	//发送加密buf
				printf("send failed\n");
				exit(1);
			} else {
				printf("send succeed\n\n");
			}
			memset(encryption_auto_upload_All_meg, 0,  sizeof(encryption_auto_upload_All_meg));	//清除加密buf
			memset(auto_upload_All_meg, 0, sizeof(auto_upload_All_meg));

			i_01 = 0;i_02 = 0;
			upload_Current_01 = 0;
			upload_Voltage_01 = 0;
			upload_Active_power_01 = 0;
			upload_Electricity_Quantity_01 = 0;
			upload_Leakage_current_01 = 0;
			upload_Temperature_01 = 0;

			upload_Current_02 = 0;
			upload_Voltage_02 = 0;
			upload_Active_power_02 = 0;
			upload_Electricity_Quantity_02 = 0;
			upload_Leakage_current_02 = 0;
			upload_Temperature_02 = 0;
		}
		if(TotalNum == 3) {
			flo_to_str(upload_Current_01/(i_01*1.0), upload_Current_01_buf, 3);
			flo_to_str_V(upload_Voltage_01/(i_01*1.0), upload_Voltage_01_buf, 1);
			flo_to_str(upload_Active_power_01/(i_01*1000.0), upload_Active_power_01_buf, 4);
			flo_to_str(upload_Electricity_Quantity_01/(i_01*1.0), upload_Electricity_Quantity_01_buf, 2);
			sprintf(upload_Leakage_current_01_buf, "%d", upload_Leakage_current_01/i_01);
			sprintf(upload_Temperature_01_buf, "%02d", upload_Temperature_01/i_01);
			sprintf(Fault_type_01_buf, "%02d", Fault_type_01);

			flo_to_str(upload_Current_02/(i_02*1.0), upload_Current_02_buf, 3);
			flo_to_str_V(upload_Voltage_02/(i_02*1.0), upload_Voltage_02_buf, 1);
			flo_to_str(upload_Active_power_02/(i_02*1000.0), upload_Active_power_02_buf, 4);
			flo_to_str(upload_Electricity_Quantity_02/(i_02*1.0), upload_Electricity_Quantity_02_buf, 2);
			sprintf(upload_Leakage_current_02_buf, "%d", upload_Leakage_current_02/i_02);
			sprintf(upload_Temperature_02_buf, "%02d", upload_Temperature_02/i_02);
			sprintf(Fault_type_02_buf, "%02d", Fault_type_02);

			flo_to_str(upload_Current_03/(i_03*1.0), upload_Current_03_buf, 3);
			flo_to_str_V(upload_Voltage_03/(i_03*1.0), upload_Voltage_03_buf, 1);
			flo_to_str(upload_Active_power_03/(i_03*1000.0), upload_Active_power_03_buf, 4);
			flo_to_str(upload_Electricity_Quantity_03/(i_03*1.0), upload_Electricity_Quantity_03_buf, 2);
			sprintf(upload_Leakage_current_03_buf, "%d", upload_Leakage_current_03/i_03);
			sprintf(upload_Temperature_03_buf, "%02d", upload_Temperature_03/i_03);
			sprintf(Fault_type_03_buf, "%02d", Fault_type_03);

			get_mac(Mac, sizeof(Mac));
			getTimestamp(Stamp);
			strcat(auto_upload_All_meg, "#cc#0101#");
			strcat(auto_upload_All_meg, Mac);
			strcat(auto_upload_All_meg, "#00SB#7.1.1#000000#0028#03#");
			strcat(auto_upload_All_meg, Stamp);

			strcat(auto_upload_All_meg, "#01;");
			strcat(auto_upload_All_meg, upload_Voltage_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_01_buf);

			strcat(auto_upload_All_meg, "#02;");
			strcat(auto_upload_All_meg, upload_Voltage_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_02_buf);

			strcat(auto_upload_All_meg, "#03;");
			strcat(auto_upload_All_meg, upload_Voltage_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_03_buf);
			strcat(auto_upload_All_meg, "#");

			auto_upload_All_meg[strlen(auto_upload_All_meg)] = '\0';
			printf("auto_upload_All_meg:%s\n", auto_upload_All_meg);
			add_secret(auto_upload_All_meg, encryption_auto_upload_All_meg);
			if((send(sockfd, encryption_auto_upload_All_meg, strlen(encryption_auto_upload_All_meg)+1, 0)) == -1) {	//发送加密buf
				printf("send failed\n");
				exit(1);
			} else {
				printf("send succeed\n\n");
			}
			memset(encryption_auto_upload_All_meg, 0,  sizeof(encryption_auto_upload_All_meg));	//清除加密buf
			memset(auto_upload_All_meg, 0, sizeof(auto_upload_All_meg));

			i_01 = 0;i_02 = 0;i_03 = 0;
			upload_Current_01 = 0;
			upload_Voltage_01 = 0;
			upload_Active_power_01 = 0;
			upload_Electricity_Quantity_01 = 0;
			upload_Leakage_current_01 = 0;
			upload_Temperature_01 = 0;

			upload_Current_02 = 0;
			upload_Voltage_02 = 0;
			upload_Active_power_02 = 0;
			upload_Electricity_Quantity_02 = 0;
			upload_Leakage_current_02 = 0;
			upload_Temperature_02 = 0;

			upload_Current_03 = 0;
			upload_Voltage_03 = 0;
			upload_Active_power_03 = 0;
			upload_Electricity_Quantity_03 = 0;
			upload_Leakage_current_03 = 0;
			upload_Temperature_03 = 0;
		}
		if(TotalNum == 4) {
			flo_to_str(upload_Current_01/(i_01*1.0), upload_Current_01_buf, 3);
			flo_to_str_V(upload_Voltage_01/(i_01*1.0), upload_Voltage_01_buf, 1);
			flo_to_str(upload_Active_power_01/(i_01*1000.0), upload_Active_power_01_buf, 4);
			flo_to_str(upload_Electricity_Quantity_01/(i_01*1.0), upload_Electricity_Quantity_01_buf, 2);
			sprintf(upload_Leakage_current_01_buf, "%d", upload_Leakage_current_01/i_01);
			sprintf(upload_Temperature_01_buf, "%02d", upload_Temperature_01/i_01);
			sprintf(Fault_type_01_buf, "%02d", Fault_type_01);

			flo_to_str(upload_Current_02/(i_02*1.0), upload_Current_02_buf, 3);
			flo_to_str_V(upload_Voltage_02/(i_02*1.0), upload_Voltage_02_buf, 1);
			flo_to_str(upload_Active_power_02/(i_02*1000), upload_Active_power_02_buf, 4);
			flo_to_str(upload_Electricity_Quantity_02/(i_02*1.0), upload_Electricity_Quantity_02_buf, 2);
			sprintf(upload_Leakage_current_02_buf, "%d", upload_Leakage_current_02/i_02);
			sprintf(upload_Temperature_02_buf, "%02d", upload_Temperature_02/i_02);
			sprintf(Fault_type_02_buf, "%02d", Fault_type_02);


			flo_to_str(upload_Current_03/(i_03*1.0), upload_Current_03_buf, 3);
			flo_to_str_V(upload_Voltage_03/(i_03*1.0), upload_Voltage_03_buf, 1);
			flo_to_str(upload_Active_power_03/(i_03*1000.0), upload_Active_power_03_buf, 4);
			flo_to_str(upload_Electricity_Quantity_03/(i_03*1.0), upload_Electricity_Quantity_03_buf, 2);
			sprintf(upload_Leakage_current_03_buf, "%d", upload_Leakage_current_03/i_03);
			sprintf(upload_Temperature_03_buf, "%02d", upload_Temperature_03/i_03);
			sprintf(Fault_type_03_buf, "%02d", Fault_type_03);

			flo_to_str(upload_Current_04/(i_04*1.0), upload_Current_04_buf, 3);
			flo_to_str_V(upload_Voltage_04/(i_04*1.0), upload_Voltage_04_buf, 1);
			flo_to_str(upload_Active_power_04/(i_04*1000.0), upload_Active_power_04_buf, 4);
			flo_to_str(upload_Electricity_Quantity_04/(i_04*1.0), upload_Electricity_Quantity_04_buf, 2);
			sprintf(upload_Leakage_current_04_buf, "%d", upload_Leakage_current_04/i_04);
			sprintf(Fault_type_04_buf, "%02d", Fault_type_04);
			sprintf(upload_Temperature_04_buf, "%02d", upload_Temperature_04/i_04);

			get_mac(Mac, sizeof(Mac));
			getTimestamp(Stamp);
			strcat(auto_upload_All_meg, "#cc#0101#");
			strcat(auto_upload_All_meg, Mac);
			strcat(auto_upload_All_meg, "#00SB#7.1.1#000000#0028#04#");
			strcat(auto_upload_All_meg, Stamp);

			strcat(auto_upload_All_meg, "#01;");
			strcat(auto_upload_All_meg, upload_Voltage_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_01_buf);

			strcat(auto_upload_All_meg, "#02;");
			strcat(auto_upload_All_meg, upload_Voltage_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_02_buf);

			strcat(auto_upload_All_meg, "#03;");
			strcat(auto_upload_All_meg, upload_Voltage_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_03_buf);

			strcat(auto_upload_All_meg, "#04;");
			strcat(auto_upload_All_meg, upload_Voltage_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_04_buf);
			strcat(auto_upload_All_meg, "#");

			auto_upload_All_meg[strlen(auto_upload_All_meg)] = '\0';
			printf("strlen(auto_upload_All_meg):%d\n", strlen(auto_upload_All_meg));

			printf("auto_upload_All_meg:%s\n", auto_upload_All_meg);
			add_secret(auto_upload_All_meg, encryption_auto_upload_All_meg);
			printf("encryption_auto_upload_All_meg:%s\n", encryption_auto_upload_All_meg);
			if((send(sockfd, encryption_auto_upload_All_meg, strlen(encryption_auto_upload_All_meg)+1, 0)) == -1) {	//发送加密buf
				printf("send failed\n");
				exit(1);
			} else {
				printf("send succeed\n\n");
			}
			memset(encryption_auto_upload_All_meg, 0,  sizeof(encryption_auto_upload_All_meg));	//清除加密buf
			memset(auto_upload_All_meg, 0, sizeof(auto_upload_All_meg));
#if 1
			i_01 = 0;i_02 = 0;i_03 = 0;i_04 = 0;
			upload_Current_01 = 0;
			upload_Voltage_01 = 0;
			upload_Active_power_01 = 0;
			upload_Electricity_Quantity_01 = 0;
			upload_Leakage_current_01 = 0;
			upload_Temperature_01 = 0;

			upload_Current_02 = 0;
			upload_Voltage_02 = 0;
			upload_Active_power_02 = 0;
			upload_Electricity_Quantity_02 = 0;
			upload_Leakage_current_02 = 0;
			upload_Temperature_02 = 0;

			upload_Current_03 = 0;
			upload_Voltage_03 = 0;
			upload_Active_power_03 = 0;
			upload_Electricity_Quantity_03 = 0;
			upload_Leakage_current_03 = 0;
			upload_Temperature_03 = 0;

			upload_Current_04 = 0;
			upload_Voltage_04 = 0;
			upload_Active_power_04 = 0;
			upload_Electricity_Quantity_04 = 0;
			upload_Leakage_current_04 = 0;
			upload_Temperature_04 = 0;
#endif
		}
		if(TotalNum == 5) {
			flo_to_str(upload_Current_01/(i_01*1.0), upload_Current_01_buf, 3);
			flo_to_str_V(upload_Voltage_01/(i_01*1.0), upload_Voltage_01_buf, 1);
			flo_to_str(upload_Active_power_01/(i_01*1000.0), upload_Active_power_01_buf, 4);
			flo_to_str(upload_Electricity_Quantity_01/(i_01*1.0), upload_Electricity_Quantity_01_buf, 2);
			sprintf(upload_Leakage_current_01_buf, "%d", upload_Leakage_current_01/i_01);
			sprintf(Fault_type_01_buf, "%02d", Fault_type_01);
			sprintf(upload_Temperature_01_buf, "%02d", upload_Temperature_01/i_01);

			flo_to_str(upload_Current_02/(i_02*1.0), upload_Current_02_buf, 3);
			flo_to_str_V(upload_Voltage_02/(i_02*1.0), upload_Voltage_02_buf, 1);
			flo_to_str(upload_Active_power_02/(i_02*1000.0), upload_Active_power_02_buf, 4);
			flo_to_str(upload_Electricity_Quantity_02/(i_02*1.0), upload_Electricity_Quantity_02_buf, 2);
			sprintf(upload_Leakage_current_02_buf, "%d", upload_Leakage_current_02/i_02);
			sprintf(Fault_type_02_buf, "%02d", Fault_type_02);
			sprintf(upload_Temperature_02_buf, "%02d", upload_Temperature_02/i_02);


			flo_to_str(upload_Current_03/(i_03*1.0), upload_Current_03_buf, 3);
			flo_to_str_V(upload_Voltage_03/(i_03*1.0), upload_Voltage_03_buf, 1);
			flo_to_str(upload_Active_power_03/(i_03*1000.0), upload_Active_power_03_buf, 4);
			flo_to_str(upload_Electricity_Quantity_03/(i_03*1.0), upload_Electricity_Quantity_03_buf, 2);
			sprintf(upload_Leakage_current_03_buf, "%d", upload_Leakage_current_03/i_03);
			sprintf(Fault_type_03_buf, "%02d", Fault_type_03);
			sprintf(upload_Temperature_03_buf, "%02d", upload_Temperature_03/i_03);

			flo_to_str(upload_Current_04/(i_04*1.0), upload_Current_04_buf, 3);
			flo_to_str_V(upload_Voltage_04/(i_04*1.0), upload_Voltage_04_buf, 1);
			flo_to_str(upload_Active_power_04/(i_04*1000.0), upload_Active_power_04_buf, 4);
			flo_to_str(upload_Electricity_Quantity_04/(i_04*1.0), upload_Electricity_Quantity_04_buf, 2);
			sprintf(upload_Leakage_current_04_buf, "%d", upload_Leakage_current_04/i_04);
			sprintf(Fault_type_04_buf, "%02d", Fault_type_04);
			sprintf(upload_Temperature_04_buf, "%02d", upload_Temperature_04/i_04);

			flo_to_str(upload_Current_05/(i_05*1.0), upload_Current_05_buf, 3);
			flo_to_str_V(upload_Voltage_05/(i_05*1.0), upload_Voltage_05_buf, 1);
			flo_to_str(upload_Active_power_05/(i_05*1000.0), upload_Active_power_05_buf, 4);
			flo_to_str(upload_Electricity_Quantity_05/(i_05*1.0), upload_Electricity_Quantity_05_buf, 2);
			sprintf(upload_Leakage_current_05_buf, "%d", upload_Leakage_current_05/i_05);
			sprintf(Fault_type_05_buf, "%02d", Fault_type_05);
			sprintf(upload_Temperature_05_buf, "%02d", upload_Temperature_05/i_05);

			get_mac(Mac, sizeof(Mac));
			getTimestamp(Stamp);
			strcat(auto_upload_All_meg, "#cc#0101#");
			strcat(auto_upload_All_meg, Mac);
			strcat(auto_upload_All_meg, "#00SB#7.1.1#000000#0028#05#");
			strcat(auto_upload_All_meg, Stamp);

			strcat(auto_upload_All_meg, "#01;");
			strcat(auto_upload_All_meg, upload_Voltage_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_01_buf);

			strcat(auto_upload_All_meg, "#02;");
			strcat(auto_upload_All_meg, upload_Voltage_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_02_buf);

			strcat(auto_upload_All_meg, "#03;");
			strcat(auto_upload_All_meg, upload_Voltage_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_03_buf);

			strcat(auto_upload_All_meg, "#04;");
			strcat(auto_upload_All_meg, upload_Voltage_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_04_buf);

			strcat(auto_upload_All_meg, "#05;");
			strcat(auto_upload_All_meg, upload_Voltage_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_05_buf);
			strcat(auto_upload_All_meg, "#");

			auto_upload_All_meg[strlen(auto_upload_All_meg)] = '\0';
			printf("auto_upload_All_meg:%s\n", auto_upload_All_meg);
			add_secret(auto_upload_All_meg, encryption_auto_upload_All_meg);
			if((send(sockfd, encryption_auto_upload_All_meg, strlen(encryption_auto_upload_All_meg)+1, 0)) == -1) {	//发送加密buf
				printf("send failed\n");
				exit(1);
			} else {
				printf("send succeed\n\n");
			}
			memset(encryption_auto_upload_All_meg, 0,  sizeof(encryption_auto_upload_All_meg));	//清除加密buf
			memset(auto_upload_All_meg, 0, sizeof(auto_upload_All_meg));

			i_01 = 0;i_02 = 0;i_03 = 0;i_04 = 0;i_05 = 0;
			upload_Current_01 = 0;
			upload_Voltage_01 = 0;
			upload_Active_power_01 = 0;
			upload_Electricity_Quantity_01 = 0;
			upload_Leakage_current_01 = 0;
			upload_Temperature_01 = 0;

			upload_Current_02 = 0;
			upload_Voltage_02 = 0;
			upload_Active_power_02 = 0;
			upload_Electricity_Quantity_02 = 0;
			upload_Leakage_current_02 = 0;
			upload_Temperature_02 = 0;

			upload_Current_03 = 0;
			upload_Voltage_03 = 0;
			upload_Active_power_03 = 0;
			upload_Electricity_Quantity_03 = 0;
			upload_Leakage_current_03 = 0;
			upload_Temperature_03 = 0;

			upload_Current_04 = 0;
			upload_Voltage_04 = 0;
			upload_Active_power_04 = 0;
			upload_Electricity_Quantity_04 = 0;
			upload_Leakage_current_04 = 0;
			upload_Temperature_04 = 0;

			upload_Current_05 = 0;
			upload_Voltage_05 = 0;
			upload_Active_power_05 = 0;
			upload_Electricity_Quantity_05 = 0;
			upload_Leakage_current_05 = 0;
			upload_Temperature_05 = 0;

		}
		if(TotalNum == 6) {
			flo_to_str(upload_Current_01/(i_01*1.0), upload_Current_01_buf, 3);
			flo_to_str_V(upload_Voltage_01/(i_01*1.0), upload_Voltage_01_buf, 1);
			flo_to_str(upload_Active_power_01/(i_01*1000.0), upload_Active_power_01_buf, 4);
			flo_to_str(upload_Electricity_Quantity_01/(i_01*1.0), upload_Electricity_Quantity_01_buf, 2);
			sprintf(upload_Leakage_current_01_buf, "%d", upload_Leakage_current_01/i_01);
			sprintf(Fault_type_01_buf, "%02d", Fault_type_01);
			sprintf(upload_Temperature_01_buf, "%02d", upload_Temperature_01/i_01);

			flo_to_str(upload_Current_02/(i_02*1.0), upload_Current_02_buf, 3);
			flo_to_str_V(upload_Voltage_02/(i_02*1.0), upload_Voltage_02_buf, 1);
			flo_to_str(upload_Active_power_02/(i_02*1000.0), upload_Active_power_02_buf, 4);
			flo_to_str(upload_Electricity_Quantity_02/(i_02*1.0), upload_Electricity_Quantity_02_buf, 2);
			sprintf(upload_Leakage_current_02_buf, "%d", upload_Leakage_current_02/i_02);
			sprintf(Fault_type_02_buf, "%02d", Fault_type_02);
			sprintf(upload_Temperature_02_buf, "%02d", upload_Temperature_02/i_02);


			flo_to_str(upload_Current_03/(i_03*1.0), upload_Current_03_buf, 3);
			flo_to_str_V(upload_Voltage_03/(i_03*1.0), upload_Voltage_03_buf, 1);
			flo_to_str(upload_Active_power_03/(i_03*1000.0), upload_Active_power_03_buf, 4);
			flo_to_str(upload_Electricity_Quantity_03/(i_03*1.0), upload_Electricity_Quantity_03_buf, 2);
			sprintf(upload_Leakage_current_03_buf, "%d", upload_Leakage_current_03/i_03);
			sprintf(Fault_type_03_buf, "%02d", Fault_type_03);
			sprintf(upload_Temperature_03_buf, "%02d", upload_Temperature_03/i_03);

			flo_to_str(upload_Current_04/(i_04*1.0), upload_Current_04_buf, 3);
			flo_to_str_V(upload_Voltage_04/(i_04*1.0), upload_Voltage_04_buf, 1);
			flo_to_str(upload_Active_power_04/(i_04*1000.0), upload_Active_power_04_buf, 4);
			flo_to_str(upload_Electricity_Quantity_04/(i_04*1.0), upload_Electricity_Quantity_04_buf, 2);
			sprintf(upload_Leakage_current_04_buf, "%d", upload_Leakage_current_04/i_04);
			sprintf(Fault_type_04_buf, "%02d", Fault_type_04);
			sprintf(upload_Temperature_04_buf, "%02d", upload_Temperature_04/i_04);

			flo_to_str(upload_Current_05/(i_05*1.0), upload_Current_05_buf, 3);
			flo_to_str_V(upload_Voltage_05/(i_05*1.0), upload_Voltage_05_buf, 1);
			flo_to_str(upload_Active_power_05/(i_05*1000.0), upload_Active_power_05_buf, 4);
			flo_to_str(upload_Electricity_Quantity_05/(i_05*1.0), upload_Electricity_Quantity_05_buf, 2);
			sprintf(upload_Leakage_current_05_buf, "%d", upload_Leakage_current_05/i_05);
			sprintf(Fault_type_05_buf, "%02d", Fault_type_05);
			sprintf(upload_Temperature_05_buf, "%02d", upload_Temperature_05/i_05);

			flo_to_str_V(upload_Voltage_06/(i_06*1.0), upload_Voltage_06_buf, 3);
			flo_to_str(upload_Current_06/(i_06*1.0), upload_Current_06_buf, 1);
			flo_to_str(upload_Active_power_06/(i_06*1000.0), upload_Active_power_06_buf, 4);
			flo_to_str(upload_Electricity_Quantity_06/(i_06*1.0), upload_Electricity_Quantity_06_buf, 2);
			sprintf(upload_Temperature_06_buf, "%02d", upload_Temperature_06/i_06);
			sprintf(Fault_type_06_buf, "%02d", Fault_type_06);
			sprintf(upload_Leakage_current_06_buf, "%d", upload_Leakage_current_06/i_06);

			get_mac(Mac, sizeof(Mac));
			getTimestamp(Stamp);
			strcat(auto_upload_All_meg, "#cc#0101#");
			strcat(auto_upload_All_meg, Mac);
			strcat(auto_upload_All_meg, "#00SB#7.1.1#000000#0028#06#");
			strcat(auto_upload_All_meg, Stamp);

			strcat(auto_upload_All_meg, "#01;");
			strcat(auto_upload_All_meg, upload_Voltage_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_01_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_01_buf);

			strcat(auto_upload_All_meg, "#02;");
			strcat(auto_upload_All_meg, upload_Voltage_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_02_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_02_buf);

			strcat(auto_upload_All_meg, "#03;");
			strcat(auto_upload_All_meg, upload_Voltage_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_03_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_03_buf);

			strcat(auto_upload_All_meg, "#04;");
			strcat(auto_upload_All_meg, upload_Voltage_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_04_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_04_buf);

			strcat(auto_upload_All_meg, "#05;");
			strcat(auto_upload_All_meg, upload_Voltage_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_05_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_05_buf);

			strcat(auto_upload_All_meg, "#06;");
			strcat(auto_upload_All_meg, upload_Voltage_06_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Current_06_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Active_power_06_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Electricity_Quantity_06_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Temperature_06_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, Fault_type_06_buf);
			strcat(auto_upload_All_meg, ";");
			strcat(auto_upload_All_meg, upload_Leakage_current_06_buf);
			strcat(auto_upload_All_meg, "#");

			auto_upload_All_meg[strlen(auto_upload_All_meg)] = '\0';
			printf("auto_upload_All_meg:%s\n", auto_upload_All_meg);
			add_secret(auto_upload_All_meg, encryption_auto_upload_All_meg);
			if((send(sockfd, encryption_auto_upload_All_meg, strlen(encryption_auto_upload_All_meg)+1, 0)) == -1) {	//发送加密buf
				printf("send failed\n");
				exit(1);
			} else {
				printf("send succeed\n\n");
			}
			memset(encryption_auto_upload_All_meg, 0,  sizeof(encryption_auto_upload_All_meg));	//清除加密buf
			memset(auto_upload_All_meg, 0, sizeof(auto_upload_All_meg));

			i_01 = 0;i_02 = 0;i_03 = 0;i_04 = 0;i_05 = 0;i_06 = 0;
			upload_Current_01 = 0;
			upload_Voltage_01 = 0;
			upload_Active_power_01 = 0;
			upload_Electricity_Quantity_01 = 0;
			upload_Leakage_current_01 = 0;
			upload_Temperature_01 = 0;

			upload_Current_02 = 0;
			upload_Voltage_02 = 0;
			upload_Active_power_02 = 0;
			upload_Electricity_Quantity_02 = 0;
			upload_Leakage_current_02 = 0;
			upload_Temperature_02 = 0;

			upload_Current_03 = 0;
			upload_Voltage_03 = 0;
			upload_Active_power_03 = 0;
			upload_Electricity_Quantity_03 = 0;
			upload_Leakage_current_03 = 0;
			upload_Temperature_03 = 0;

			upload_Current_04 = 0;
			upload_Voltage_04 = 0;
			upload_Active_power_04 = 0;
			upload_Electricity_Quantity_04 = 0;
			upload_Leakage_current_04 = 0;
			upload_Temperature_04 = 0;

			upload_Current_05 = 0;
			upload_Voltage_05 = 0;
			upload_Active_power_05 = 0;
			upload_Electricity_Quantity_05 = 0;
			upload_Leakage_current_05 = 0;
			upload_Temperature_05 = 0;

			upload_Current_06 = 0;
			upload_Voltage_06 = 0;
			upload_Active_power_06 = 0;
			upload_Electricity_Quantity_06 = 0;
			upload_Leakage_current_06 = 0;
			upload_Temperature_06 = 0;

		}

	}

#endif
}




