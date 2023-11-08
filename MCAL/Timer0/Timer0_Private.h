#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

 typedef struct
 {
 	u8 CS00	:1;
 	u8 CS01	:1;
 	u8 CS02	:1;
 	u8 WGM01:1;
 	u8 COM00:1;
 	u8 COM01:1;
 	u8 WGM00:1;
 	u8 FOC0	:1;
 }T0_TCCR0_Bits;
 
 typedef union
 {
 	u8 Reg;
 	T0_TCCR0_Bits Bits;
 }T0_TCCR0_t;
 
 typedef struct
 {
 	u8 SFIOR;
 	u8 RES0[1];
 	u8 TCNT0;
 	T0_TCCR0_t TCCR0;
 	u8 RES1[4];
 	u8 TIFR;
 	u8 TIMSK;
 	u8 RES2[2];
 	u8 OCR0;
 	}T0_Reg_t;


#define T0 (*(volatile T0_Reg_t*)0x50)



#define	T0_NORMAL					1
#define T0_CTC						2
#define T0_FASTPWM					3
#define T0_PCPWM					4


#define T0_PRESCALER_1				1
#define T0_PRESCALER_8				2
#define T0_PRESCALER_64				3
#define T0_PRESCALER_256			4
#define T0_PRESCALER_1024			5

#define	T0_FASTPWM_INVERTING		1
#define	T0_FASTPWM_NONINVERTING		2

#define	T0_PCPWM_INVERTING			1
#define	T0_PCPWM_NONINVERTING		2
/*
// 
// 
// //========================(Control Registers)=================================
// #define T0_TCCR0 (*(volatile TIMER0_TCCR0_Types*)0x53)
// //========================(	Data Registers)===================================
// #define T0_TCNT0 (*(volatile U8*)0x52)
// #define T0_OCR0 (*(volatile U8*)0x5C)
// //========================(Interrupt Registers)================================
// #define T0_TIMSK (*(volatile U8*)0x59)
// #define TOIE0_Bit 0
// #define OCIE0_Bit 1
// #define T0_TIFR (*(volatile U8*)0x58)
// #define TOV0_Bit 0
// #define OCF0_Bit 1
// //========================(Special FunctionIO Registers)========================
// #define T0_SFIOR (*(volatile U8*)0x50)
// #define PSR10_Bit 0
// //========================(DIO Channal For Timer0)==============================
// #define TIMER0_DIO_Channel DIO_ChannelB3
*/

#endif /* TIMER0_PRIVATE_H_ */