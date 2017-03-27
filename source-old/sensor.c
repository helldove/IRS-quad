#include "headers/sensor.h"


int init_spi(REG_BASE cmper_base, REG_BASE ctrl_base, REG_BASE spi_base){
	TYPE_8 mode = SPI_MODE_0;
	TYPE_32 speed = SPEED_HZ;
	TYPE_8 nLSB = 0;
	TYPE_8 bits = 8;


	int fd;
	printf("\\spi init start\n");

	if(!set_reg((TYPE_32)(cmper_base + CMPER_SPI0), 2, 32,OW))
		printf("failed to set register - CMPER_SPI0\n");
	if(!set_reg((TYPE_32)(cmper_base + CMPER_SPI1), 2, 32,OW))
		printf("failed to set register - CMPER_SPI1\n");

	fd = open(SENSOR_FD,O_RDWR);
	if(fd < 0 ){
		printf("init spi fd_l open error");
		return 0;
	}

	if(ioctl(fd, SPI_IOC_WR_MODE,&mode) == -1){
		printf("failed to set SPI WR MODE to MODE 0\n");
		return 0;
	}
	if(ioctl(fd, SPI_IOC_RD_MODE,&mode) == -1){
		printf("failed to set SPI RD MODE to MODE 0\n");
		return 0;
	}
	if(ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ,&speed) == -1){
		printf("failed to set SPI WR MAX SPEED HZ to 20000000\n");
		return 0;
	}
	if(ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ,&speed) == -1){
		printf("failed to set SPI RD MAX SPEED HZ to 20000000\n");
		return 0;
	}
	if(ioctl(fd, SPI_IOC_WR_LSB_FIRST, &nLSB) == -1){
		printf("failed to set SPI WR LSB FIRSL to 0\n");
		return 0;
	}
	if(ioctl(fd, SPI_IOC_RD_LSB_FIRST, &nLSB) == -1){
		printf("failed to set SPI RD LSB FIRSL to 0\n");
		return 0;
	}
	if(ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1){
		printf("failed to set SPI WR BITS PER WORD to 16\n");
		return 0;
	}
	if(ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) == -1){
		printf("failed to set SPI RD BITS PER WORD to 16\n");
		return 0;
	}
	//for MPU-6000 gyro sensor
	//schedule_delay_ms(100);
	//device reset
	spi_reg_set(fd,0x6B,0x80);
	schedule_delay_ms(101);
	//I2C disable
	spi_reg_set(fd,0x6A,0x10);
	schedule_delay_ms(101);
	//sleep disable, clksel maximum
	spi_reg_set(fd,0x6B,0x00);
	schedule_delay_ms(101);
	//Data ready INT enable
	spi_reg_set(fd,0x38,0x01);
	schedule_delay_ms(5);
	//Data ready INT clear
	spi_reg_set(fd,0x37,0x10);
	schedule_delay_ms(5);
	//gyro full scale range set to +- 1000
	spi_reg_set(fd,0x1B,0x10);
	schedule_delay_ms(5);
	//accelerometer foll scale range set to +-8g
	spi_reg_set(fd,0x1C,0x10);
	schedule_delay_ms(5);
	//digital low pass filter set to 20Hz
	spi_reg_set(fd,0x1A,0x00);
	schedule_delay_ms(5);

	printf("\\spi init complete\n");

	return fd;
}

TYPE_8 spi_transfer(int fd, TYPE_8 data){
	TYPE_8 rx = 0;
	struct spi_ioc_transfer spi1_struct = {
		.tx_buf = (unsigned long)&data,
		.rx_buf = (unsigned long)&rx,
		.len = 1,
		.speed_hz = SPEED_HZ,
		.bits_per_word = 8,
		.cs_change = 1
	};
	if(ioctl(fd, SPI_IOC_MESSAGE(1), &spi1_struct) == -1)
		printf("failed to communicate spi\n");

	return rx;
}

void spi_transfer_array(int fd, TYPE_8 * data, TYPE_8 * rxbuf, TYPE_8 lent){
	int i;

	struct spi_ioc_transfer spi1_struct = {
		.tx_buf = (unsigned long)data,
		.rx_buf = (unsigned long)rxbuf,
		.len = lent,
		.speed_hz = SPEED_HZ,
		.bits_per_word = 8,
		.cs_change = 1
	};
	if(ioctl(fd, SPI_IOC_MESSAGE(1), &spi1_struct) == -1)
		printf("failed to communicate spi\n");

	return;
}

void spi_reg_set(int fd, TYPE_8 addr, TYPE_8 data){
	TYPE_8 txxbuf[2] = {addr,data};
	TYPE_8 rxxbuf[2];
	spi_transfer_array(fd,txxbuf,rxxbuf,sizeof(txxbuf));
	return;
}

void sensor_get_acc(int fd, double * x_acc, double * y_acc, double * z_acc){
	TYPE_8 rxbuf[7];
	TYPE_8 txbuf[7] = {0x3B|0x80,0,0,0,0,0,0};
	int16_t temp = 0;
	memset(rxbuf,0,sizeof (rxbuf));
	#ifdef DEBUG
		printf("==========get acc value from sensor==========\n");
	#endif
	spi_transfer_array(fd,txbuf,rxbuf,sizeof(txbuf));
	#ifdef DEBUG
		printf("==============end get acc value ==============\n");
	#endif
	temp = rxbuf[1]<<8 | rxbuf[2];
	*x_acc = (double)temp/4096.0*9.8;
	temp = rxbuf[3]<<8 | rxbuf[4];
	*y_acc = (double)temp/4096.0*9.8;
	temp = rxbuf[5]<<8 | rxbuf[6];
	*z_acc = (double)temp/4096.0*9.8;
	return;
}

void sensor_get_gyro(int fd, double * x_gyro, double * y_gyro, double * z_gyro){
	TYPE_8 rxbuf[7];
	TYPE_8 txbuf[7] = {0x43|0x80,0,0,0,0,0,0};
	int16_t temp = 0;
	memset(rxbuf,0,sizeof (rxbuf));
	#ifdef DEBUG
		printf("==========get gyro value from sensor==========\n");
	#endif
	spi_transfer_array(fd,txbuf,rxbuf,sizeof(txbuf));
	#ifdef DEBUG
		printf("==============end get gyro value ==============\n");
	#endif
	temp = rxbuf[1]<<8 | rxbuf[2];
	*x_gyro = (double)temp/32.8;
	temp = rxbuf[3]<<8 | rxbuf[4];
	*y_gyro = (double)temp/32.8;
	temp = rxbuf[5]<<8 | rxbuf[6];
	*z_gyro = (double)temp/32.8;
	return;
}

void sensor_get_who_am_i(int fd, unsigned short * whoami){
	TYPE_8 rxbuf[3];
	TYPE_8 txbuf[3] = {0x75 | 0x80, 0,0};
	printf("==========get who am i value from sensor==========\n");
	spi_transfer_array(fd,txbuf,rxbuf,sizeof(txbuf));
	printf("==============end get who am i value ==============\n");

	*whoami = rxbuf[1]<<8 | rxbuf[2];
	return;
}

void cal_theta(double xyacc, double zacc, double * theta){
	double temp = atan2(xyacc,zacc)*180/M_PI;
	*theta = *theta * 0.20 + temp * 0.80;
}

