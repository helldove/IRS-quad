#ifndef CLK_H_INCLUDE
#define CLK_H_INCLUDE

//CMPER register address
#define CMPER_BASE_START 0x44E00000
#define CMPER_BASE_END 0x44E03FFF
#define CMPER_SIZE CMPER_BASE_END - CMPER_BASE_START

//CMPER OFFSET ADDRESS
#define CMPER_L4LS_ST 0x000
#define CMPER_L3S_ST 0x004
#define CMPER_L3_ST 0x00C
#define CMPER_CPGMAC0 0x014
#define CMPER_LCDC 0x018
#define CMPER_USB0 0x01C
#define CMPER_TPTC0 0x024
#define CMPER_EMIF 0x028
#define CMPER_OCMCRAM 0x02C
#define CMPER_GPMC 0x030
#define CMPER_MCASP0 0x034
#define CMPER_UART5 0x038
#define CMPER_MMC0 0X03C
#define CMPER_ELM 0x040
#define CMPER_I2C2 0x044
#define CMPER_I2C1 0x048
#define CMPER_SPI0 0x04C
#define CMPER_SPI1 0x050
#define CMPER_L4LS 0x060
#define CMPER_MCASP1 0x068
#define CMPER_UART1 0x06C
#define CMPER_UART2 0x070
#define CMPER_UART3 0x074
#define CMPER_UART4 0x078
#define CMPER_TIMER7 0x07C
#define CMPER_TIMER2 0x080
#define CMPER_TIMER3 0x084
#define CMPER_TIMER4 0x088
#define CMPER_GPIO1 0x0AC
#define CMPER_GPIO2 0x0B0
#define CMPER_GPIO3 0x0B4
#define CMPER_TPCC 0x0BC
#define CMPER_DCAN0 0x0C0
#define CMPER_DCAN1 0x0C4
#define CMPER_EPWMSS1 0x0CC
#define CMPER_EPWMSS0 0x0D4
#define CMPER_EPWMSS2 0x0D8
#define CMPER_L3_INSTR 0x0DC
#define CMPER_L3 0x0E0
#define CMPER_IEEE5000 0x0E4
#define CMPER_PRU_ICSS 0x0E8
#define CMPER_TIMER5 0x0EC
#define CMPER_TIMER6 0x0F0
#define CMPER_MMC1 0x0F4
#define CMPER_MMC2 0x0F8
#define CMPER_TPTC1 0x0FC
#define CMPER_TPTC2 0x100
#define CMPER_SPINLOCK 0x10C
#define CMPER_MAILBOX0 0x110
#define CMPER_L4HS_ST 0x11C
#define CMPER_L4HS 0x120
#define CMPER_OCPWP_L3_ST 0x12C
#define CMPER_OCPWP 0x130
#define CMPER_PRU_ICSS_ST 0x140
#define CMPER_CPWS_ST 0x144
#define CMPER_LCDC_ST 0x148
#define CMPER_CLKDIV32K 0x14C
#define CMPER_CLK_24MHZ_ST 0x150


#endif