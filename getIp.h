#ifndef _GETIP_H_
#define _GETIP_H_

#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "config.h"

uint8_t* GetLocalIp(void);

#endif
