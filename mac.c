#include "mac.h"

int get_mac(uint8_t * mac, int len_limit) {  //返回值是实际写入char * mac的字符个数（不包括'\0'）
	struct ifreq ifreq;
	int sock;

	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		perror ("socket");
		return -1;
	}
	strcpy (ifreq.ifr_name, "eth0");    //Currently, only get eth0

	if (ioctl (sock, SIOCGIFHWADDR, &ifreq) < 0) {
		perror ("ioctl");
		return -1;
	}
	//git mac,output.
	return snprintf (mac, len_limit, "%06X%02X%02X%02X%02X%02X",
	                 (uint8_t) ifreq.ifr_hwaddr.sa_data[0], \
	                 (uint8_t) ifreq.ifr_hwaddr.sa_data[1], \
	                 (uint8_t) ifreq.ifr_hwaddr.sa_data[2], \
	                 (uint8_t) ifreq.ifr_hwaddr.sa_data[3], \
	                 (uint8_t) ifreq.ifr_hwaddr.sa_data[4], \
	                 (uint8_t) ifreq.ifr_hwaddr.sa_data[5]);
}

