#ifndef _PRINT_H
#define _PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#define LOG_PRINT( fmt, args ... )	printf( fmt, ##args );
#define EXIT(n)	exit(n);
#define ERR_PRINT( fmt, args ... ) printf("%s:%s:%d:%s: "#fmt, __FILE__, __FUNCTION__, __LINE__, strerror(errno), ##args );


#endif

