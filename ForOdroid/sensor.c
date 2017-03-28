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

#include "sensor.h"

//switching slave address to gyro accellerometer
#define SWGA(a)		{if(ioctl(a,I2C_SLAVE,GAADDR)<0){ \
						printf("error at switching slave address to gyro accel\n");}}
//switching slave address to mag
#define SWMG(a)		{if(ioctl(a,I2C_SLAVE,MGADDR)<0){ \
						printf("error at switching slave address to mag\n");}}

int mpuInit(void){
	int fd = open(SENSOR_FD,O_RDWR);
	if(fd<0){
		printf("error to open i2c dev\n");
		return -1;
	}
	if(ioctl(fd,I2C_TENBIT,0)<0){
		printf("failed to set slave address length to 7\n");
		printf("maybe this SoC basically has only 7bit address protocol\n");
	}

	SWGA(fd);
}