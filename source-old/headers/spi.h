#ifndef SPI_H_INCLUDE
#define SPI_H_INCLUDE

//MCSPI0 register address
#define MCSPI0_BASE_START 0x48030000
#define MCSPI0_BASE_END 0x48030FFF
#define MCSPI0_SIZE MCSPI0_BASE_END - MCSPI0_BASE_START

//MCSPI1 register address
#define MCSPI1_BASE_START 0x481A0000
#define MCSPI1_BASE_END 0x481A0FFF
#define MCSPI1_SIZE MCSPI1_BASE_END - MCSPI1_BASE_START

//MCSPI offset address
#define MCSPI_REVISION 0x000
#define MCSPI_SYSCONFIG 0x110
#define MCSPI_SYSSTATUS 0x114
#define MCSPI_IRQSTATUS 0x118
#define MCSPI_IRQENABLE 0x11C
#define MCSPI_SYST 0x124
#define MCSPI_MODYLECTRL 0x128
#define MCSPI_CH0CONF 0x12C
#define MCSPI_CH0STAT 0x130
#define MCSPI_CH0CTRL 0x134
#define MCSPI_TX0 0x138
#define MCSPI_RX0 0x13C
#define MCSPI_CH1CONF 0x140
#define MCSPI_CH1STAT 0x144
#define MCSPI_CH1CTRL 0x148
#define MCSPI_TX1 0x14C
#define MCSPI_RX1 0x150
#define MCSPI_CH2CONF 0x154
#define MCSPI_CH2STAT 0x158
#define MCSPI_CH2CTRL 0x15C
#define MCSPI_TX2 0x160
#define MCSPI_RX2 0x164
#define MCSPI_CH3CONF 0x168
#define MCSPI_CH3STAT 0x16C
#define MCSPI_CH3CTRL 0x170
#define MCSPI_TX3 0x174
#define MCSPI_RX3 0x178
#define MCSPI_XFERLEVEL 0x17C
#define MCSPI_DAFTX 0x180
#define MCSPI_DAFRX 0x1A0



#endif