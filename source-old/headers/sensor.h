#ifndef SENSOR_H_INCLUDE
#define SENSOR_H_INCLUDE

#include "base.h"
#include "ctrl.h"
#include "clk.h"
#include "spi.h"
#include "gpio.h"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <math.h>

#define SENSOR_FD "/dev/spidev1.0"
#define SPEED_HZ 10000000

#define RG 0.4
#define RA 0.0004



extern int init_spi(REG_BASE cmper_base, REG_BASE ctrl_base, REG_BASE spi_base);
extern TYPE_8 spi_transfer(int fd, TYPE_8 data);
extern void spi_transfer_array(int fd, TYPE_8 * data, TYPE_8 * rxbuf, TYPE_8 lent);
extern void spi_reg_set(int fd, TYPE_8 addr, TYPE_8 data);
extern void sensor_get_acc(int fd, double * x_acc, double * y_acc, double * z_acc);
extern void sensor_get_gyro(int fd, double * x_gyro, double * y_gyro, double * z_gyro);
extern void cal_theta(double xyacc, double zacc, double * theta);
extern void sensor_get_who_am_i(int fd, unsigned short * whoami);

#endif
