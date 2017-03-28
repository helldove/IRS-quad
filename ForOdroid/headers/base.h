#ifndef BASE_H_INCLUDE
#define BASE_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <errno.h>
#include <linux/fs.h>
#include <getopt.h>
#include <sys/ioctl.h>

#define X	0
#define Y	1
#define Z	2

float gyro[3];
float accel[3];
float magnet[3];





#endif