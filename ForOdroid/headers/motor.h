#ifndef MOTOR_H_INCLUDE
#define MOTOR_H_INCLUDE

#include "base.h"
#include <stdlib.h>
#include <unistd.h>

#define MOTORDIR	"/sys/devices/platform/pwm-ctrl"
#define DUTY		"/duty"
#define FREQ		"/freq"
#define ENPWM		"/enable"
#define PWMFREQ		490
#define PWMMIN		512
#define PWMMAX		1023

extern int duty[2];

void pwmInit(void);
void pwmSpeed(int flag,int speed);
void pwmDeinit(void);


#endif