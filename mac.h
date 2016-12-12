#ifndef _MAC_H_
#define _MAC_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>        //for struct ifreq
#include "config.h"

int get_mac(uint8_t * mac, int len_limit);

#endif
