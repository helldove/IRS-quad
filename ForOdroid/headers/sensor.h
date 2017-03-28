/***********************************************************
 *	Intelligent System Quad-rotor
 *  based ubuntu mate (linux 3.14.79-93)
 *	sensor : MPU-9255
 *	board : odroid c2
 *	motor & mechanism : chinese unknown
 *	using basic device driver
 *
 *	Author : Sangwook Ha , Junghan Shin
 *
 *	this source for sensor communication on i2c protocol
 ***********************************************************/

#ifndef SENSOR_H_INCLUDE
#define SENSOR_H_INCLUDE

#include "base.h"
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define SENSOR_FD 	"/dev/i2c-1"	// pin 2,3
#define GAADDR		0x68		//if AD0pin is high, LSB set to 1
#define MGADDR		0x0C		//magnatic sensor i2c address


int mpuInit(void);



#endif

