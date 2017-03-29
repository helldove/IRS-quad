#include "headers/base.h"
#include "headers/motor.h"

//sudo modprobe pwm-meson npwm=2
//sudo modprobe pwm-ctrl


int main(void){
	int SelectPwm = 0,PwmSpeed = 0;

	printf("pwm start\n");
	pwmInit();
	printf("initializing finish\n");
	pwmSpeed(2,700);
	printf("period : %d %%\n",70000/1023);
	sleep(5);
	pwmDeinit();
	printf("pwm end\n");

	return 0;
}