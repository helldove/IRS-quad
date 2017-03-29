#include "headers/motor.h"

int duty[2]={0};

void pwmInit(void){
	char temp[50];
	int freq = 0, en = 0,i=0;
	for(i=0;i<2;i++){
		sprintf(temp,"%s%s%d",MOTORDIR,FREQ,i);
		freq = open(temp,O_WRONLY|O_TRUNC);
		printf("%s : %d\n",temp,freq);
		sprintf(temp,"%d",PWMFREQ);
		write(freq,temp,3);
		close(freq);
	}
	for(i=0;i<2;i++){
		sprintf(temp,"%s%s%d",MOTORDIR,DUTY,i);
		duty[i] = open(temp,O_WRONLY|O_TRUNC);
		printf("%s : %d\n",temp,duty[i]);
		sprintf(temp,"%d",PWMMIN);
		write(duty[i],temp,3);
	}
	for(i=0;i<2;i++){
		sprintf(temp,"%s%s%d",MOTORDIR,ENPWM,i);
		en = open(temp,O_WRONLY|O_TRUNC);
		printf("%s : %d\n",temp,en);	
		write(en,"1",1);
		close(en);
	}
	sleep(8);
}


void pwmSpeed(int flag, int speed){
	char temp[5];
	if(speed > PWMMAX)
		speed = PWMMAX;
	else if(speed < PWMMIN)
		speed = PWMMIN;

	sprintf(temp,"%d",speed);
	switch(flag){
		case 0:
			write(duty[0],temp,4);
			break;
		case 1:
			write(duty[1],temp,4);
			break;
		default:
			write(duty[0],temp,4);
			write(duty[0],temp,4);
			break;
	}
}

void pwmDeinit(void){
	char temp[50];
	int en = 0,i=0;
	for(i=0;i<2;i++){
		sprintf(temp,"%s%s%d",MOTORDIR,FREQ,i);
		en = open(temp,O_WRONLY|O_TRUNC);	
		printf("%s : %d\n",temp,en);	
		write(en,"0",1);
		close(en);
		close(duty[i]);
	}
}