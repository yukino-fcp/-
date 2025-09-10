#ifndef COMM_H
#define COMM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSERR(x,option,y,message,z)	if((x) option (y))		\
																						{						\
																							printf("%s %s %d : %s\n",__FILE__,__func__,__LINE__,message);\
																							return z;			\
																						}
#define LOOPCOUNT 3
#define ADMIN_NAME "admin"
#define ADMIN_PASS "8"
#define DEV_FILE "device.dat"

#endif
