#ifndef _CLIENT_HF_H_
#define _CLIENT_HF_H_

#include "print.h"
#include "config.h"

#include <sys/ioctl.h>
#include <linux/watchdog.h>
#include <sys/time.h>
#include <time.h>


#define BACKLOG 10

void thread_wait(void);
void thread_create(void);
void *thread_send();
void *thread_recv();
void Send_Recv(void);
void get_sz_buffer(uint8_t *sp, uint8_t *buffer);
void kill_program(void);
int getNum(uint8_t* s);
void *thread_first(void * arg);
void *thread_C();



//hahahah

#endif
