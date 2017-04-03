#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define TARGET		"/dev/GPIO_LED"

int main(void){
	int fd,inmem,datas,i;
	char Buff[4] = {0};
	char wrmem;
	printf("GPIO Device Driver LED test program\n Author : Sangwook Ha\n");
	fd = open(TARGET,O_RDWR);
	if(fd<0){
		printf("device driver open error\n");
		return 1;
	}
	while(1){
		LOOP:
		printf("which mode?\nWrite: 1\nRead: 2\nexit: 3\n");
		scanf("%d",&inmem);
		/*
		if(inmem>3 || inmem<1){
			printf("mode setting error\n");
			goto LOOP;
		}*/
		if(inmem == 1){
			ioctl(fd,1);
		}
		else if(inmem == 2){
			ioctl(fd,3);
		}
		else if(inmem == 3){
			break;
		}
		else{
			printf("mode setting error\n");
			goto LOOP;
		}
		//ioctl(fd,inmem);
		switch(inmem){
			case 2:
				printf("now Pin read states :\n");
				read(fd,Buff,4);
				datas = (Buff[0]<<24)|(Buff[1]<<16)|(Buff[2]<<8)|Buff[3];
				for(i=0;i<23;i++)
					printf("Pin %d : %d\n",i,(datas>>i)&1);
			break;
			case 1:
				printf("which pin set do you want?\n");
				printf("0~22 or 30(all) : ");
				scanf("%d",&datas);
				if(datas == 30)
					wrmem = 'a';
				else
					wrmem = datas;
				write(fd,&wrmem,1);
			break;
		}
	
	}
	close(fd);
	return 0;
}
