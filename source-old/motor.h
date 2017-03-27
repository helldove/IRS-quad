#ifndef MOTOR_H_INCLUDE
#define MOTOR_H_INCLUDE

#include "base.h"
#include "pwm.h"
#include "gpio.h"
#include "ctrl.h"
#include "clk.h"

#define MOTOR_MIN 0x30D4   //12500
#define MOTOR_MAX 0x61A8   //25000
//#define MOTOR_MAX 0xC350   //50000
#define MOTOR_VAL(a) (int)(((a)*(MOTOR_MAX-MOTOR_MIN)/100)+MOTOR_MIN)

#define MA_DUTY(a) ((a) + 0x200 + PWMSS_EPWM_CMPA)
#define MB_DUTY(a) ((a) + 0x200 + PWMSS_EPWM_CMPB)


extern int init_pwm(REG_BASE cmper_base, REG_BASE ctrl_base, REG_BASE pwm1_base, REG_BASE pwm2_base, double hz);
extern int set_duty(REG_BASE motor, double dutyval);


#endif