#ifndef TIMER_H_INCLUDE
#define TIMER_H_INCLUDE

//DMTIMER0 register address
#define DMRIMER0_BASE_START 0x44E05000
#define DMTIMER0_BASE_END 0x44E05FFF
#define DMTIMER0_SIZE DMTIMER0_BASE_END - DMTIMER0_BASE_START

//DMTIMER1 register address (1ms timer)
#define DMTIMER1_BASE_START 0x44E31000
#define DMTIMER1_BASE_END 0x44E31FFF
#define DMTIMER1_SIZE DMTIMER1_BASE_END - DMTIMER1_BASE_START

//DMTIMER2 register address
#define DMTIMER2_BASE_START 0x48040000
#define DMTIMER2_BASE_END 0x48040FFF
#define DMTIMER2_SIZE DMTIMER2_BASE_END - DMTIMER2_BASE_START

//DMTIMER3 register address
#define DMTIMER3_BASE_START 0x48042000
#define DMTIMER3_BASE_END 0x48042FFF
#define DMTIMER3_SIZE DMTIMER3_BASE_END - DMTIMER3_BASE_START

//DMTIMER4 register address
#define DMTIMER4_BASE_START 0x48044000
#define DMTIMER4_BASE END 0x48044FFF
#define DMTIMER4_SIZE DMTIMER4_BASE_END - DMTIMER4_BASE_START

//DMTIMER5 register address
#define DMTIMER5_BASE_START 0x48046000
#define DMTIMER5_BASE_END 0x48046FFF
#define DMTIMER5_SIZE DMTIMER5_BASE_END - DMTIMER5_BASE_START

//DMTIMER6 register address
#define DMTIMER6_BASE_START 0x48048000
#define DMTIMER6_BASE_END 0x48048FFF
#define DMTIMER6_SIZE DMTIMER6_BASE_END - DMTIMER6_BASE_START

//DMTIMER7 register address
#define DMTIMER7_BASE_START 0x4804A000
#define DMTIMER7_BASE_END 0x4804AFFF
#define DMTIMER7_SIZE DMTIMER7_B ASE_END - DMTIMER7_BASE_START

//offset adress
#define DMTIMER_TIDR 0x000
#define DMTIMER_TIOCP_CFG 0x010
#define DMTIMER_IRQ_EOI 0x020
#define DMTIMER_IRQSTATUS_RAW 0x024
#define DMTIMER_IRQSTATUS 0x028
#define DMTIMER_IRQENABLE_SET 0x02C
#define DMTIMER_IRQENABLE_CLR 0x030
#define DMTIMER_IRQWAKEEN 0x034
#define DMTIMER_TCLR 0x038
#define DMTIMER_TCRR 0x03C
#define DMTIMER_TLDR 0x040
#define DMTIMER_TTGR 0x044
#define DMTIMER_TWPS 0x048
#define DMTIMER_TMAR 0x04C
#define DMTIMER_TCAR1 0x050
#define DMTIMER_TSICR 0x054
#define DMTIMER_TCAR2 0x058


#endif