#include "headers/motor.h"

int init_pwm(REG_BASE cmper_base, REG_BASE ctrl_base, REG_BASE pwm1_base, REG_BASE pwm2_base, double hz){
	double clk = 100000000.0f;
	double div = 0.0f;
	int i,j;
	
	int NearCLKDIV =7;
	int NearHSPCLKDIV =7;
	int cmpV = 0;
	const float CLKDIV_div[] = {1.0 ,2.0 ,4.0 ,8.0 ,16.0 ,32.0 , 64.0 , 128.0};
	const float HSPCLKDIV_div[] ={1.0 ,2.0 ,4.0 ,6.0 ,8.0 ,10.0 , 12.0 , 14.0};
	
	REG_BASE pwm1_epwm;
	REG_BASE pwm2_epwm;
	
	clk /= hz;
	div = clk / 65535.0f;
	if(div > (128*14)){
		printf("value is over than divisor\\\\value : %.3lf\n",div);
		return 0;
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if((CLKDIV_div[i] * HSPCLKDIV_div[j]) < (CLKDIV_div[NearCLKDIV] * HSPCLKDIV_div[NearHSPCLKDIV]) && ((CLKDIV_div[i] * HSPCLKDIV_div[j]) > div)) {
					NearCLKDIV = i ;
					NearHSPCLKDIV = j ;
			}
		}
	}
	
	cmpV = (int)((100000000.0/(CLKDIV_div[NearCLKDIV] * HSPCLKDIV_div[NearHSPCLKDIV]))/hz);

	pwm1_epwm = pwm1_base + 0x200;
	pwm2_epwm = pwm2_base + 0x200;
	
	#ifdef DEBUG
		printf("\\\\pwm1 epwm : %p//\n\\\\pwm2 epwm : %p//\n",pwm1_epwm,pwm2_epwm);
		
	#endif
		
	
	if(!set_reg((TYPE_32)(cmper_base + CMPER_EPWMSS0), 2, 32,OW))
		printf("failed to set register - CMPER_EPWMSS0\n");
	if(!set_reg((TYPE_32)(cmper_base + CMPER_EPWMSS1), 2, 32,OW))
		printf("failed to set register - CMPER_EPWMSS1\n");
	if(!set_reg((TYPE_32)(cmper_base + CMPER_EPWMSS2), 2, 32,OW))
		printf("failed to set register - CMPER_EPWMSS2\n");
	
	if(!set_reg((TYPE_32)(ctrl_base + CTRL_PWMSS), (1<<2 | 1<<1 | 1<<0), 32, OW))
		printf("failed to set register - CTRL_PWMSS\n");
	
	if(!set_reg((TYPE_32)(pwm2_base + PWMSS_CLKCONFIG), (1<<8 | 1<<4 | 1<<0), 32, OW))
		printf("failed to set register - PWMSS0_CLKCONFIG\n");
	if(!set_reg((TYPE_32)(pwm1_base + PWMSS_CLKCONFIG), (1<<8 | 1<<4 | 1<<0), 32, OW))
		printf("failed to set register - PWMSS1_CLKCONFIG\n");
	
	if(!set_reg((TYPE_32)(pwm1_epwm + PWMSS_EPWM_TBCTL), (NearCLKDIV <<10) | (NearHSPCLKDIV << 7) | (3<<4), 16, OW))
		printf("failed to set register - PWMSS1_EPWM_TBCTL\n");
	if(!set_reg((TYPE_32)(pwm1_epwm + PWMSS_EPWM_TBPRD), cmpV, 16, OW)) 
		printf("failed to set register - PWMSS1_EPWM_TBPRD\n");
	if(!set_reg((TYPE_32)(pwm1_epwm + PWMSS_EPWM_AQCTLA), 0x12, 16, OW))
		printf("failed to set register - PWMSS1_EPWM_AQCTLA\n");
	if(!set_reg((TYPE_32)(pwm1_epwm + PWMSS_EPWM_AQCTLB), 0x102, 16, OW))
		printf("failed to set register - PWMSS1_EPWM_AQCTLB\n");
	if(!set_reg((TYPE_32)(pwm1_epwm + PWMSS_EPWM_CMPA), 0, 16, OW))
		printf("failed to set register - PWMSS1_EPWM_CMPA\n");
	if(!set_reg((TYPE_32)(pwm1_epwm + PWMSS_EPWM_CMPB), 0, 16, OW))
		printf("failed to set register - PWMSS1_EPWM_CMPB\n");
		
	if(!set_reg((TYPE_32)(pwm2_epwm + PWMSS_EPWM_TBCTL), (NearCLKDIV <<10) | (NearHSPCLKDIV << 7) | (0<<0) | (0<<5) | (0<<4), 16, OW))
		printf("failed to set register - PWMSS2_EPWM_TBCTL\n");
	if(!set_reg((TYPE_32)(pwm2_epwm + PWMSS_EPWM_TBPRD), cmpV, 16, OW)) 
		printf("failed to set register - PWMSS2_EPWM_TBPRD\n");
	if(!set_reg((TYPE_32)(pwm2_epwm + PWMSS_EPWM_AQCTLA), 0x12, 16, OW))
		printf("failed to set register - PWMSS2_EPWM_AQCTLA\n");
	if(!set_reg((TYPE_32)(pwm2_epwm + PWMSS_EPWM_AQCTLB), 0x102, 16, OW))
		printf("failed to set register - PWMSS2_EPWM_AQCTLB\n");
	if(!set_reg((TYPE_32)(pwm2_epwm + PWMSS_EPWM_CMPA), 0, 16, OW))
		printf("failed to set register - PWMSS2_EPWM_CMPA\n");
	if(!set_reg((TYPE_32)(pwm2_epwm + PWMSS_EPWM_CMPB), 0, 16, OW))
		printf("failed to set register - PWMSS2_EPWM_CMPB\n");
	
	#ifdef DEBUG
		printf("====mux value====\n");
		printf("\\\\pwm1B=GPIO1-19(P9-16) : %08X\t\tpwm1A=GPIO1-18(P9-14) : %08X//\n",get_reg((TYPE_32)(ctrl_base + CTRL_GPMC_A(3)),32),get_reg((TYPE_32)(ctrl_base + CTRL_GPMC_A(2)),32));
		printf("\\\\pwm2B=GPIO0-23(P8-19) : %08X\t\tpwm2A=GPIO0-22(P8-13) : %08X//\n",get_reg((TYPE_32)(ctrl_base + CTRL_GPMC_AD(8)),32),get_reg((TYPE_32)(ctrl_base + CTRL_GPMC_AD(9)),32));
		printf("=================\n");
	#endif
	
	return 1;
}

int set_duty(REG_BASE motor, double dutyper){
	int temp = 0;
	if(dutyper>100.0)
		dutyper = 100.0;
	if(dutyper <= 0.0)
		dutyper = 0.0;
	temp = ((int)(dutyper));
	if(!set_reg((TYPE_32)motor, MOTOR_VAL(temp), 16, OW))
		return 0;
	
	return 1;
}
