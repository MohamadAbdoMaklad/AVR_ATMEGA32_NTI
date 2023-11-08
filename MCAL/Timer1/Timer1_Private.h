#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_
#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"
typedef struct
{
	u8 WGM10_Bit:1;
	u8 WGM11_Bit:1;
	u8 FOC1B_Bit:1;
	u8 FOC1A_Bit:1;
	u8 COM1B0_Bit:1;
	u8 COM1B1_Bit:1;
	u8 COM1A0_Bit:1;
	u8 COM1A1_Bit:1;
}T1_TCCR1A_Bits;

typedef union{
	u8 AllRegister;
	T1_TCCR1A_Bits Bits;
}T1_TCCR1A_t;


typedef struct
{
	u8 CS10_Bit:1;
	u8 CS11_Bit:1;
	u8 CS12_Bit:1;
	u8 WGM12_Bit:1;
	u8 WGM13_Bit:1;
	u8 RESERVED_Bit:1;
	u8 ICES1_Bit:1;
	u8 ICNC1_Bit:1;
}T1_TCCR1B_Bits;

typedef union{
	u8 AllRegister;
	T1_TCCR1B_Bits Bits;
}T1_TCCR1B_t;

typedef struct
{
	u16			ICR1		;
	u16			OCR1B		;
	u16			OCR1A		;
	u16			TCNT1		;
	T1_TCCR1B_t	TCCR1B		;
	T1_TCCR1A_t	TCCR1A		;	
	u8			RES1[8]		;
	u8			TIFR		;
	u8			TIMSK		;		
}T1_Reg_t;		
	
#define T1 (*(volatile T1_Reg_t*)0x46)

/*Timer 1 Modes*/
#define T1_NORMAL_M0	1
#define T1_CTC_M4		5
#define T1_FastPWM_M14	15
/*T1_FastPWM_M14 Modes*/
#define T1_PWM_NONINVERTING 1
#define T1_PWM_INVERTING 2
/*Timer 1 Prescaler Values*/
#define T1_PRESCALER_1				1
#define T1_PRESCALER_8				2
#define T1_PRESCALER_64				3
#define T1_PRESCALER_256			4
#define T1_PRESCALER_1024			5


#endif /* TIMER1_PRIVATE_H_ */

