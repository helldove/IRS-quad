/*     [3]
//      |
// [1]--O--[0]
//      |
//     [2]
*/

#include "headers/motor.h"
#include "headers/sensor.h"
#include "headers/base.h"
#include "headers/controlsys.h"
#include <sys/shm.h>
#include <math.h>

#define ACC 0
#define GYRO 1
#define Tilda2Force 0.0375

int fd_mem, fd_spi;
REG_BASE pwm1_base;
REG_BASE pwm2_base;
REG_BASE ctrl_base;
REG_BASE cmper_base;
REG_BASE spi_base;


//value[0] is acc, value[1] is gyro
double mx[2] = {0,0};
double my[2] = {0,0};
double mz[2] = {0,0};

double roll_theta = 0.0;
double pitch_phi = 0.0;

double tar_theta = 0.0;
double tar_phi = 0.0;

double theta_control = 0.0;
double phi_control = 0.0;

double theta_force = 0.0;
double phi_force = 0.0;

double pwm_val[4] = {5.0,5.0,5.0,5.0};

unsigned short whoami = 0;

//check for tic us
//compensation delay for realtime
struct timeval ts;
int time_temp;
//struct sched_param sp = {.sched_priority = 1};

int main(void){
	int i=0,j=0;

	nice(-18);
	/*
	if(sched_setscheduler(0, SCHED_FIFO, &sp) == -1){
		perror("sched_setcheduler");
		return 1;
	}*/
	fd_mem = init_mem(&cmper_base, &ctrl_base, &pwm1_base, &pwm2_base, &spi_base);
	fd_spi = init_spi(cmper_base, ctrl_base, spi_base);
	if(fd_mem < 0 || fd_spi < 0)
		printf("fd open error");
	if(!init_pwm(cmper_base, ctrl_base, pwm1_base, pwm2_base,250.0))
		printf("failed to init pwm\n");

	printf("init complete\n");

	set_duty(MA_DUTY(pwm1_base),0.0);
	set_duty(MB_DUTY(pwm1_base),0.0);
	set_duty(MA_DUTY(pwm2_base),0.0);
	set_duty(MB_DUTY(pwm2_base),0.0);

	schedule_delay_ms(10000);


	set_duty(MA_DUTY(pwm1_base),pwm_val[0]);
	set_duty(MB_DUTY(pwm1_base),pwm_val[2]);
	set_duty(MA_DUTY(pwm2_base),pwm_val[1]);
	set_duty(MB_DUTY(pwm2_base),pwm_val[3]);

	printf("**********while start***********\n");
	
	while(!kbhit()){
		#ifdef DEBUG
			printf("///////////////////////////////////////////////////////\n");
		#endif

		sensor_get_acc(fd_spi, &mx[ACC], &my[ACC], &mz[ACC]);
		sensor_get_gyro(fd_spi, &mx[GYRO], &my[GYRO], &mz[GYRO]);
		//sensor_get_who_am_i(fd_spi,&whoami);
		gettimeofday(&ts,NULL); //get us time for compensation delay
		time_temp = ts.tv_usec;

		roll_theta -= my[GYRO] * 0.005;
		pitch_phi += mx[GYRO] * 0.005;

		cal_theta(mx[ACC],mz[ACC],&roll_theta);
		cal_theta(my[ACC],mz[ACC],&pitch_phi);

		if(5.0<roll_theta || -5.0>roll_theta){
			theta_control = RollControl(0,roll_theta,&RollPrevErr,&RollDevSum);
			theta_force = theta_control*0.00828;

			pwm_val[2] += (M_PI*(theta_force*0.5+2.22241)-8133.441)/4061.7504;
			pwm_val[3] -= (M_PI*(theta_force*0.5+2.22241)-8133.441)/4061.7504;

			set_duty(MB_DUTY(pwm1_base),pwm_val[2]);
			set_duty(MB_DUTY(pwm2_base),pwm_val[3]);
		}
		if(5.0<pitch_phi || -5.0>pitch_phi){
			phi_control = PitchControl(0,pitch_phi,&PitchPrevErr,&PitchDevSum);
			phi_force = phi_control*0.00828;

			pwm_val[1] += (M_PI*(phi_force*0.5+2.22241)-8133.441)/4061.7504;
			pwm_val[0] -= (M_PI*(phi_force*0.5+2.22241)-8133.441)/4061.7504;

			set_duty(MA_DUTY(pwm1_base),pwm_val[0]);
			set_duty(MA_DUTY(pwm2_base),pwm_val[1]);
		}

		//inertia tensor Ixx : 0.018, Iyy : 0.018 
		//L is constant to 0.46m

		//theta_force = theta_control*0.0375;
		
		
		#ifdef DEBUG
			printf("\\\\theta_force : %lf\n\\\\phi_force : %lf",theta_force,phi_force);

		#endif
			
		//pwm_val[2] -= (((theta_force*30-626.3866)/425345.6528)*100);
		//pwm_val[3] += (((theta_force*30-626.3866)/425345.6528)*100);


		//pwm_val[1] -= (((phi_force*30-626.3866)/425345.6528)*100);
		//pwm_val[0] += (((phi_force*30-626.3866)/425345.6528)*100);


		#ifdef _DEBUG
			printf("\\\\motor 2 : %lf\n\\\\motor 3 : %lf\n",pwm_val[2],pwm_val[3]);
			printf("\\\\motor 1 : %lf\n\\\\motor 0 : %lf\n",pwm_val[1],pwm_val[0]);
		#endif

		
		

		
		

		gettimeofday(&ts,NULL);
		time_temp = 5000 - (time_temp - ts.tv_usec);
		if(time_temp > 0)
			schedule_delay_us(time_temp);
		//schedule_delay_ms(495);
		#ifdef _DEBUG
			printf("\\\\roll : %lf\n\\\\pitch : %lf\n",roll_theta, pitch_phi);
			printf("\\\\xacc : %lf\tyacc : %lf\tzacc : %lf\n",mx[ACC],my[ACC],mz[ACC]);
			printf("\\\\xgyro : %lf\tygyro : %lf\tzgyro : %lf\n",mx[GYRO],my[GYRO],mz[GYRO]);
		#endif
	}
	printf("***********while end************\n");

	munmap(pwm2_base, PWMSS2_SIZE);
	munmap(pwm1_base, PWMSS1_SIZE);
	munmap(ctrl_base, CTRL_SIZE);
	munmap(cmper_base, CMPER_SIZE);
	munmap(spi_base,MCSPI0_SIZE);
	close(fd_mem);
	close(fd_spi);

    return 0;
}
