#include "getIp.h"
#define ETH_NAME "eth0"

char* GetLocalIp(void) {
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ - 1] = 0;

	ioctl(sock, SIOCGIFADDR, &ifr);
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	return inet_ntoa(sin.sin_addr);
}

int Strcmp(const char* str1, const char* str2){
		const int resu1 = 0, resu2 = 1;
		int a = 0, b = 0,i = 0, j = 0;
		char ch1, ch2;
		a = strlen((char *)str1);
		b = strlen((char *)str2);
		if(a != b){
			return resu2; 
		}else{
			for(i = 0; i < a; i++){
				ch1 = *(str1+i);
				ch2 = *(str2+i);
				if(ch1 == ch2){
					j++;			
				}else{
					return resu2;
				}
			}
			if(j < i)return resu2;
			else return resu1;
		}
}


