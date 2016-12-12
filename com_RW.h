
#ifndef _COM_RW_H_
#define _COM_RW_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include "config.h"

void myDelay(int delay);
int sendCmdToSerial(void);
int readcom(void);
void analysis_Data(unsigned char *buf);
void getTimestamp(uint8_t* stamp);

extern int getnum(uint8_t* s);


#define SEND_SERIAL_INTERVAL 1000000 /// 1000000 us=1s
#define  LOG_SERIAL 1


#endif /* SERIALSERVICE_H_ */
