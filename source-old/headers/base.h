#ifndef BASE_H_INCLUDE
#define BASE_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <asm-generic/param.h>
//#include <linux/module.h>
//#include <asm/hardware.h>
//#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/types.h>
//#include <linux/ioport.h>
//#include <linux/timer.h>
//#include <linux/signal.h>
//#include <linux/jiffies.h>
#include <sys/time.h>
#include <time.h>

#define OW 0
#define OR 1
#define AND 2

#define REG_BASE void * 
#define REG_32 unsigned int *
#define REG_16 unsigned short *
#define REG_8 unsigned char *
#define TYPE_32 unsigned int
#define TYPE_16 unsigned short
#define TYPE_8 unsigned char

#define MEMORY_FD "/dev/mem"

extern char set_reg(TYPE_32 addr, TYPE_32 value, int size, int flag);
extern TYPE_32 get_reg(TYPE_32 addr, int size);
extern void addr_mmap(void ** addr, int * fd, size_t length, off_t offset);
extern int init_mem(REG_BASE * cmper_base, REG_BASE * ctrl_base, REG_BASE * pwm1_base, REG_BASE * pwm2_base, REG_BASE * spi_base);
extern void schedule_delay_us(TYPE_32 us);
extern void schedule_delay_ms(TYPE_32 ms);
extern void controller_position(double tar_theta, double tar_phi, double theta, double phi);
extern int kbhit(void);

#endif
