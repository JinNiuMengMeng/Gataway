#ifndef _COMMEND_H_
#define _COMMEND_H_

#include <stdio.h>
#include "config.h"

uint8_t * get_zc_buffer(uint8_t *buffer);

void add_secret(uint8_t *buf, uint8_t *encryption_buff);


#endif
