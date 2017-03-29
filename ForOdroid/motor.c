#include "headers/motor.h"

int duty[2]={0};

void pwmInit(void){
	char temp[100];
	int freq = 0, en = 0,i=0;
	for(i=0;i<2;i++){
		sprintf(temp,"%s%s%d",MOTORDIR,FREQ,i);
		freq = open(temp,O_WRONLY||O_TRUNC);
		sprintf(temp,"%d",PWMFREQ);
		write(freq,temp,3);
		close(freq);
	}
	sleep(1)
	for(i=0;i<2;i++){
		sprintf(temp,"echo %d > %s%s%d",PWMMIN,MOTORDIR,DUTY,i);
		//duty[i] = open(temp,O_WRONLY||O_TRUNC);
		//printf("%s : %d , ",temp,duty[i]);
		//sprintf(temp,"%d",PWMMIN);
		//printf("duty%d : %s\n",i,temp);
		//write(duty[i],temp,4);
		system(temp);
	}
	sleep(1)
	for(i=0;i<2;i++){
		sprintf(temp,"%s%s%d",MOTORDIR,ENPWM,i);
		en = open(temp,O_WRONLY||O_TRUNC);
		write(en,"1",1);
		close(en);
	}
	sleep(8);
}


void pwmSpeed(int flag, int speed){
	char temp[100];
	if(speed > PWMMAX)
		speed = PWMMAX;
	else if(speed < PWMMIN)
		speed = PWMMIN;

	//sprintf(temp,"%d",speed);
	//printf("input speed : %s\n",temp);
	switch(flag){
		case 0:
			//write(duty[0],temp,4);
			//printf("pwm0 %s \n",temp);
			sprintf(temp,"echo %d > %s%s%d",speed,MOTORDIR,DUTY,0);
			system(temp);
			break;
		case 1:
			//write(duty[1],temp,4);
			//printf("pwm1 %s \n",temp);
			sprintf(temp,"echo %d > %s%s%d",speed,MOTORDIR,DUTY,1);
			system(temp);
			break;
		default:
			//write(duty[0],temp,4);
			//write(duty[1],temp,4);
			//printf("pwm0&1 %s \n",temp);
			sprintf(temp,"echo %d > %s%s%d",speed,MOTORDIR,DUTY,0);
			system(temp);
			sprintf(temp,"echo %d > %s%s%d",speed,MOTORDIR,DUTY,1);
			system(temp);
			break;
	}
}

void pwmDeinit(void){
	char temp[50];
	int en = 0,i=0;
	for(i=0;i<2;i++){
		sprintf(temp,"%s%s%d",MOTORDIR,ENPWM,i);
		en = open(temp,O_WRONLY||O_TRUNC);		
		write(en,"0",1);
		close(en);
		close(duty[i]);
	}
}