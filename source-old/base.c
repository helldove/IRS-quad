/*
* name : base.c
* author : sangwook ha
*
* description :  functions of setting regisers
*/


#include "headers/base.h"
#include "headers/spi.h"
#include "headers/ctrl.h"
#include "headers/clk.h"
#include "headers/gpio.h"
#include "headers/pwm.h"
#include "headers/intc.h"
#include "headers/timer.h"
#include <sys/select.h> 

//set register bits
//flag :  OW = overwrite, OR = or operation, AND = and operation 
char set_reg(TYPE_32 addr, TYPE_32 value, int size, int flag){
	static REG_8 temp_8;
	static REG_16 temp_16;
	static REG_32 temp_32;
	static char sel = 0;
	static TYPE_32 temp_value;
	#ifdef DEBUG
		printf("\\\\in set_reg  addr : %p\n",addr);
	#endif
	switch(size){
		case 8:
			temp_8 = (REG_8)(addr);
			temp_value = (TYPE_8) *temp_8;
			sel = 8;
			#ifdef DEBUG
				printf("\\\\in set_reg address set finish temp_8 : %p\n",temp_8);
			#endif
			break;
		case 16:
			temp_16 = (REG_16)(addr);
			temp_value = (TYPE_32) *temp_16;
			sel = 16;
			#ifdef DEBUG
				printf("\\\\in set_reg address set finish temp_16 : %p\n",temp_16);
			#endif
			break;
		case 32:
			temp_32 = (REG_32)(addr);
			temp_value = *temp_32;
			sel = 32;
			#ifdef DEBUG
				printf("\\\\in set_reg address set finish temp_32 : %p\n",temp_32);
			#endif
			break;
		default:
			return 0;
	}
	switch(sel){
		case 8:
			switch(flag){
				case OW:
					*temp_8 = (TYPE_8)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,value,*temp_8);
					#endif
					if(*temp_8 != (TYPE_8)value)
						return 0;
					return 1;
				case OR:
					*temp_8 |= (TYPE_8)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,(temp_value | value),*temp_8);
                    #endif
					if(*temp_8 != (TYPE_8)(temp_value | value))
						return 0;
					return 1;
				case AND:
					*temp_8 &= (TYPE_8)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,(temp_value & value),*temp_8);
                    #endif
					if(*temp_8 != (TYPE_8)(temp_value & value))
						return 0;
					return 1;
				default:
					*temp_8 = (TYPE_8)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,value,*temp_8);
                    #endif
					if(*temp_8 != (TYPE_8)value)
						return 0;
					return 1;
			}
		case 16:
			switch(flag){
				case OW:
					*temp_16 = (TYPE_16)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,value,*temp_16);
					#endif
					if(*temp_16 != (TYPE_16)value)
						return 0;
					return 1;
				case OR:
					*temp_16 |= (TYPE_16)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,(temp_value | value),*temp_16);
                    #endif
					if(*temp_16 != (TYPE_16)(temp_value | value))
						return 0;
					return 1;
				case AND:
					*temp_16 &= (TYPE_16)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,(temp_value & value),*temp_16);
                    #endif
					if(*temp_16 != (TYPE_16)(temp_value & value))
						return 0;
					return 1;
				default:
					*temp_16 = (TYPE_16)value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,value,*temp_16);
                    #endif
					if(*temp_16 != (TYPE_16)value)
						return 0;
					return 1;
			}
		case 32:
			switch(flag){
				case OW:
					*temp_32 = value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,value,*temp_32);
					#endif
					if(*temp_32 != value)
						return 0;
					return 1;
				case OR:
					*temp_32 |= value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,(temp_value | value),*temp_32);
                    #endif
					if(*temp_32 != (temp_value | value))
						return 0;
					return 1;
				case AND:
					*temp_32 &= value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,(temp_value & value),*temp_32);
                    #endif
					if(*temp_32 != (temp_value & value))
						return 0;
					return 1;
				default:
					*temp_32 = value;
					#ifdef DEBUG
						printf("\\\\%p address\n\\\\input value : %08X\n\\\\in real value : %08X\n",addr,value,*temp_32);
					#endif
					if(*temp_32 != value)
						return 0;
					return 1;
			}

		default:
			return 0;
	}
}

//get register bits
TYPE_32 get_reg(TYPE_32 addr, int size){
	static REG_16 temp_16;
	static REG_32 temp_32;
	#if DEBUG
		printf("\\\\in get_reg  addr : %p\n",addr);
	#endif
	switch(size){
		case 16:
			temp_16 = (REG_16)(addr);
			return (TYPE_32)(*temp_16);
		case 32:
			temp_32 = (REG_32)(addr);
			return *temp_32;
		default:
			return 0;
	}
}

void addr_mmap(void ** addr, int * fd, size_t length, off_t offset){
	*addr = mmap(0, length, PROT_READ|PROT_WRITE, MAP_SHARED, *fd, offset);
	return;
}

int init_mem(REG_BASE * cmper_base, REG_BASE * ctrl_base, REG_BASE * pwm1_base, REG_BASE * pwm2_base, REG_BASE * spi_base){
	int fd;
	printf("\\init memory start\n");
	fd = open(MEMORY_FD,O_RDWR | O_SYNC);
	if(fd < 0 ){
		printf("init mem fd open error");
		return -1;
	}
	*cmper_base = mmap(NULL, CMPER_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, CMPER_BASE_START);
	*ctrl_base = mmap(NULL, CTRL_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, CTRL_BASE_START);
	*pwm2_base = mmap(NULL, PWMSS2_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, PWMSS2_BASE_START);
	*pwm1_base = mmap(NULL, PWMSS1_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, PWMSS1_BASE_START);	
	*spi_base =  mmap(NULL, MCSPI0_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, MCSPI0_BASE_START);
	
	#ifdef DEBUG
		printf("=================mmap base address=================\n");
		printf("\\\\fd : %d//\n", fd);
		printf("\\\\ctrl base : %p//\n\\\\cmper base : %p//\n", *ctrl_base, *cmper_base);
		printf("\\\\pwm1 base : %p//\n\\\\pwm2 base : %p//\n", *pwm1_base, *pwm2_base);
		printf("\\\\spi0 base : %p//\n", *spi_base);
		printf("===================================================\n");
	#endif
	
	printf("\\init memory complete\n");
	
	return fd;
}


void schedule_delay_us(TYPE_32 us){
	struct timeval ts;
	TYPE_32 delay = 0;
	gettimeofday(&ts,NULL);
	delay = ts.tv_usec + us;
	/*#ifdef DEBUG
		printf("====================schedule_delay_ms=================\n");
		printf("\\\\real time in nsec : %d\n",ts.tv_usec);
		printf("\\\\delay : %d\n",delay);
		printf("=======================delay start====================\n");
	#endif*/
	if(delay >= 1000000)
		delay -= 1000000;
	while(ts.tv_usec < delay){
		//#ifdef DEBUG
			//printf("\\\\now time : %d\n",ts.tv_usec);
		//#endif
		sched_yield();
		gettimeofday(&ts,NULL);
	}
	/*#ifdef DEBUG
		printf("========================delay end=====================\n");
	#endif*/
	return;
}

void schedule_delay_ms(TYPE_32 ms){
	int i=0;
	for(i=0;i<ms;i++)
		schedule_delay_us(1000);
	
	return;
}

int kbhit(void){ 
	struct timeval tv; 
	fd_set read_fd; 

	tv.tv_sec=0; 
	tv.tv_usec=0; 
	FD_ZERO(&read_fd); 
	FD_SET(0,&read_fd); 

	if(select(1, &read_fd, NULL, NULL, &tv) == -1) 
		return 0; 

	if(FD_ISSET(0,&read_fd)) 
		return 1; 

	return 0; 
} 


