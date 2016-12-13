#ifndef _GETIP_H_
#define _GETIP_H_

#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <errno.h>
#include <string.h>

char* GetLocalIp(void);

#endif
