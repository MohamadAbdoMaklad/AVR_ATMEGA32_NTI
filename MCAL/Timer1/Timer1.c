#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"

#include "Timer1_Cfg.h"
#include "Timer1_Private.h"
#include "Timer1_Interface.h"


void T1_voidInit(void)
{
	//SetMode
	#if T1_MODE == T1_FastPWM_M14
	T1.TCCR1A.Bits.WGM10_Bit =LOW;
	T1.TCCR1A.Bits.WGM11_Bit =HIGH;
	T1.TCCR1B.Bits.WGM12_Bit =HIGH;
	T1.TCCR1B.Bits.WGM13_Bit =HIGH;
		#if		T1_PWM_Mode == T1_PWM_NONINVERTING
			T1.TCCR1A.Bits.COM1A0_Bit= LOW;
			T1.TCCR1A.Bits.COM1A1_Bit= HIGH;
		#elif	T1_PWM_Mode == T1_PWM_INVERTING
			T1.TCCR1A.Bits.COM1A0_Bit= HIGH;
			T1.TCCR1A.Bits.COM1A1_Bit= HIGH;
		#endif
	#endif
}
void T1_voidStart(void)
{
	#if		T1_PRESCALER == T1_PRESCALER_1
		T1.TCCR1B.Bits.CS10_Bit	= HIGH;
		T1.TCCR1B.Bits.CS11_Bit	= LOW;
		T1.TCCR1B.Bits.CS12_Bit	= LOW;
	#elif	T1_PRESCALER ==	T1_PRESCALER_8
		T1.TCCR1B.Bits.CS10_Bit	= LOW;
		T1.TCCR1B.Bits.CS11_Bit	= HIGH;
		T1.TCCR1B.Bits.CS12_Bit	= LOW;
	#elif	T1_PRESCALER ==	T1_PRESCALER_64
		T1.TCCR1B.Bits.CS10_Bit	= HIGH;
		T1.TCCR1B.Bits.CS11_Bit	= HIGH;
		T1.TCCR1B.Bits.CS12_Bit	= LOW;
	#elif	T1_PRESCALER ==	T1_PRESCALER_256
		T1.TCCR1B.Bits.CS10_Bit	= LOW;
		T1.TCCR1B.Bits.CS11_Bit	= LOW;
		T1.TCCR1B.Bits.CS12_Bit	= HIGH;
	#elif	T1_PRESCALER ==	T1_PRESCALER_1024
		T1.TCCR1B.Bits.CS10_Bit	= HIGH;
		T1.TCCR1B.Bits.CS11_Bit	= LOW;
		T1.TCCR1B.Bits.CS12_Bit	= HIGH;
	#endif
	
	
}
void T1_voidStop(void)
{
	T1.TCCR1B.Bits.CS10_Bit	= LOW;
	T1.TCCR1B.Bits.CS11_Bit	= LOW;
	T1.TCCR1B.Bits.CS12_Bit	= LOW;
	
}
void T1_voidSetCompMatchValA(u16 copy_u16CompareMatchVal)
{
	T1.OCR1A = copy_u16CompareMatchVal;
}
void T1_SetDyty_Mode14(f32 copy_f32DytyCycleVal)
{
	#if T1_MODE == T1_FastPWM_M14
		#if		T1_PWM_Mode == T1_PWM_NONINVERTING
			T1.OCR1A = (((copy_f32DytyCycleVal*(T1.ICR1 +1))/100)-1);
		#elif	T1_PWM_Mode == T1_PWM_INVERTING
			copy_f32DytyCycleVal = 100 - copy_f32DytyCycleVal;
			T1.OCR1A = (((copy_f32DytyCycleVal*(T1.ICR1 +1))/100)-1);
		#endif
	#endif
	
	
	
	
}
void T1_SetFreq_Mode14(u16 copy_u16FreqVal)
{
	T1.ICR1 = (((1000000UL/copy_u16FreqVal)/4)-1);
}