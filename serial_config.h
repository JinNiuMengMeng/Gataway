#ifndef _SERIAL_CONFIG_H_
#define _SERIAL_CONFIG_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>

typedef struct {
	char	prompt; //prompt after reciving data
	int 	baudrate; //baudrate
	char	databit; //data bits, 5, 6, 7, 8
	char 	debug; //debug mode, 0: none, 1: debug
	char 	echo; //echo mode, 0: none, 1: echo
	char	fctl; //flow control, 0: none, 1: hardware, 2: software
	char	parity; //parity 0: none, 1: odd, 2: even
	char	stopbit; //stop bits, 1, 2
	const int reserved;	//reserved, must be zero
} portinfo_t;
typedef portinfo_t *pportinfo_t;



int convbaud(unsigned long int baudrate);
int PortSet(int fdcom, const pportinfo_t pportinfo);
void thread_create_serial(void);
void thread_wait_serial(void) ;
void Gateway_Poll(void);
/*
int PortSend(int fdcom, char *data, int datalen)
{
	int len = 0;

	len = write(fdcom, data, datalen);  //实际写入的长度
	if(len == datalen) {
		return (len);
	} else {
		tcflush(fdcom, TCOFLUSH);
		return -1;
	}
}
*/
#endif
