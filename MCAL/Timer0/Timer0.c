#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"

#include "Timer0_Private.h"
#include "Timer0_Interface.h"
#include "Timer0_cfg.h"

v_P2F_v OVFp2f = NULL;
v_P2F_v OCRp2f = NULL;
volatile static u16 CTC_localCounter = 0;


void T0_voidInit(void)
{
	#if T0_MODE == T0_NORMAL
		// select Normal Mode
		T0.TCCR0.Bits.WGM00 = LOW;
		T0.TCCR0.Bits.WGM01 = LOW;
		// Set Prelude
		T0.TCNT0 = T0_PretudeVal;
		// Enable interrupt
		SET_BIT(T0.TIMSK,0);
	#elif T0_MODE == T0_CTC
		// select CTC Mode
		T0.TCCR0.Bits.WGM00 = LOW;
		T0.TCCR0.Bits.WGM01 = HIGH;
		// Enable interrupt
		SET_BIT(T0.TIMSK,1);
	#elif T0_MODE == T0_FASTPWM
		// select Fast PWM Mode
		T0.TCCR0.Bits.WGM00 = HIGH;
		T0.TCCR0.Bits.WGM01 = HIGH;
		// Sellect inverting or non inverting
		#if		T0_FASTPWM_MODE == T0_FASTPWM_INVERTING
			T0.TCCR0.Bits.COM00 = HIGH;
			T0.TCCR0.Bits.COM01 = HIGH;
		#elif	T0_FASTPWM_MODE == T0_FASTPWM_NONINVERTING
			T0.TCCR0.Bits.COM00 = LOW;
			T0.TCCR0.Bits.COM01 = HIGH;
		#endif
	#elif T0_MODE == T0_PCPWM
		T0.TCCR0.Bits.WGM00 = HIGH;
		T0.TCCR0.Bits.WGM01 = LOW;
		// Sellect inverting or non inverting
		#if		T0_PCPWM_MODE == T0_PCPWM_INVERTING
			T0.TCCR0.Bits.COM00 = HIGH;
			T0.TCCR0.Bits.COM01 = HIGH;
		#elif	T0_PCPWM_MODE == T0_PCPWM_NONINVERTING
			T0.TCCR0.Bits.COM00 = LOW;
			T0.TCCR0.Bits.COM01 = HIGH;
		#endif
	#endif
}

void T0_voidStart(void)
{
	
	#if		T0_PRESCALER == T0_PRESCALER_1
		T0.TCCR0.Bits.CS00=HIGH;
		T0.TCCR0.Bits.CS01=LOW;
		T0.TCCR0.Bits.CS02=LOW;
	#elif	T0_PRESCALER == T0_PRESCALER_8
		T0.TCCR0.Bits.CS00=LOW;
		T0.TCCR0.Bits.CS01=HIGH;
		T0.TCCR0.Bits.CS02=LOW;
	#elif	T0_PRESCALER == T0_PRESCALER_64
		T0.TCCR0.Bits.CS00=HIGH;
		T0.TCCR0.Bits.CS01=HIGH;
		T0.TCCR0.Bits.CS02=LOW;
	#elif	T0_PRESCALER == T0_PRESCALER_256
		T0.TCCR0.Bits.CS00=LOW;
		T0.TCCR0.Bits.CS01=LOW;
		T0.TCCR0.Bits.CS02=HIGH;
	#elif	T0_PRESCALER == T0_PRESCALER_1024
		T0.TCCR0.Bits.CS00=HIGH;
		T0.TCCR0.Bits.CS01=LOW;
		T0.TCCR0.Bits.CS02=HIGH;
	#endif
	
}

void T0_voidStop(void)
{
	T0.TCCR0.Bits.CS00=LOW;
	T0.TCCR0.Bits.CS01=LOW;
	T0.TCCR0.Bits.CS02=LOW;
}

void T0_voidSetCallBackOVF(v_P2F_v copy_LP2F)
{
	if (copy_LP2F != NULL)
	{
		OVFp2f = copy_LP2F;
	}
}


void T0_voidSetCallBackCTC(v_P2F_v copy_LP2F)
{
		if (copy_LP2F != NULL)
		{
			OCRp2f = copy_LP2F;
		}
}

void T0_voidSetCompMatchVal(u8 copy_CTCVal)
{
	
	T0.OCR0 = copy_CTCVal;
	
}


void T0_voidDelay_ms_CTC(u32 copy_MS)
{
	#if		T0_PRESCALER == T0_PRESCALER_1
		//
	#elif	T0_PRESCALER == T0_PRESCALER_8
		T0.OCR0=249;
		CTC_localCounter = copy_MS;
	#elif	T0_PRESCALER == T0_PRESCALER_64
		T0.OCR0=249;
		CTC_localCounter = copy_MS*8;
	#elif	T0_PRESCALER == T0_PRESCALER_256
		//
	#elif	T0_PRESCALER == T0_PRESCALER_1024
		//
	#endif
	
}


void T0_voidSetDytyCycle_PWM(u8 copy_u8DytyCycle)
{
	
	#if		T0_MODE == T0_FASTPWM
		#if		T0_FASTPWM_MODE == T0_FASTPWM_INVERTING
		copy_u8DytyCycle=100-copy_u8DytyCycle;
		T0.OCR0 = ((((u16)copy_u8DytyCycle*256)/100)-1);
		#elif	T0_FASTPWM_MODE == T0_FASTPWM_NONINVERTING
		T0.OCR0 = ((((u16)copy_u8DytyCycle*256)/100)-1);
		#endif
	#elif	T0_MODE == T0_PCPWM
		#if		T0_PCPWM_MODE == T0_PCPWM_INVERTING
		copy_u8DytyCycle=100-copy_u8DytyCycle;
		T0.OCR0 = (((100-(u16)copy_u8DytyCycle)*255)/100);
		#elif	T0_PCPWM_MODE == T0_PCPWM_NONINVERTING
		T0.OCR0 = (((u16)copy_u8DytyCycle*255)/100);
		#endif
	#endif		
}




void __vector_11(void) __attribute__ ((signal));
void __vector_11(void)
{
	static u16 local_OVFcounter = 0;
	local_OVFcounter++;
	if(T0_OVFCounter == local_OVFcounter)
	{
		//Clear Counter
		local_OVFcounter =0;
		//prelude again
		T0.TCNT0 = T0_PretudeVal;
		// call action
		if(OVFp2f != NULL)
		{
			OVFp2f();
		}
	}
}


void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
	static u16 local_counter = 0;
	local_counter++;
	if(T0_CTCCounter == local_counter)
	{
		//Clear Counter
		local_counter =0;
		// call action
		if(OCRp2f != NULL)
		{
			OCRp2f();
		}
	}
}