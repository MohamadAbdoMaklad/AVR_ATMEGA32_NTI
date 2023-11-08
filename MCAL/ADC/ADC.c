#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"
#include "DIO.h"
#include "PORT.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"

static v_P2F_u16 ADC_GP2F_u16 = NULL;


void ADC_Init (ADC_InitTypes * OPTIONS)
{
	ADC.ADMUX.REFS = OPTIONS->adcVref;
	ADC.ADMUX.ADLAR = LOW;
	ADC.SFIOR.ADTS = OPTIONS->AutoTrigSource;
	ADC.ADCSRA.ADPS = OPTIONS->adcClock;
	ADC.ADCSRA.ADEN = HIGH;
}
u16 ADC_READ (ADC_ChannelTypes CHANNEL_NO)
{
	switch (CHANNEL_NO){
		case ADC_Channel0:Dio_SetChannelDirection(Dio_A0,INPUT);break;
		case ADC_Channel1:Dio_SetChannelDirection(Dio_A1,INPUT);break;
		case ADC_Channel2:Dio_SetChannelDirection(Dio_A2,INPUT);break;
		case ADC_Channel3:Dio_SetChannelDirection(Dio_A3,INPUT);break;
		case ADC_Channel4:Dio_SetChannelDirection(Dio_A4,INPUT);break;
		case ADC_Channel5:Dio_SetChannelDirection(Dio_A5,INPUT);break;
		case ADC_Channel6:Dio_SetChannelDirection(Dio_A6,INPUT);break;
		case ADC_Channel7:Dio_SetChannelDirection(Dio_A7,INPUT);break;
	}
	u16 ReadValue = 0;
	ADC.ADCSRA.ADSC = HIGH;
	while(!ADC.ADCSRA.ADIF);
	ADC.ADCSRA.ADIF = HIGH;
	ReadValue = ADC.ADCHL;
	//_delay_ms(1);
	return ReadValue;
}
void ADC_voidEnableInterrupt(void)
{
	ADC.ADCSRA.ADIF = HIGH;
}
void ADC_voidDisableInterrupt(void)
{
	ADC.ADCSRA.ADIF = LOW;
}
void ADC_voidReadAssynchronous(ADC_ChannelTypes CHANNEL_NO , v_P2F_u16 ADC_LP2F_u16)
{
	if (ADC_LP2F_u16 != NULL)
	{
		switch (CHANNEL_NO){
			case ADC_Channel0:Dio_SetChannelDirection(Dio_A0,INPUT);break;
			case ADC_Channel1:Dio_SetChannelDirection(Dio_A1,INPUT);break;
			case ADC_Channel2:Dio_SetChannelDirection(Dio_A2,INPUT);break;
			case ADC_Channel3:Dio_SetChannelDirection(Dio_A3,INPUT);break;
			case ADC_Channel4:Dio_SetChannelDirection(Dio_A4,INPUT);break;
			case ADC_Channel5:Dio_SetChannelDirection(Dio_A5,INPUT);break;
			case ADC_Channel6:Dio_SetChannelDirection(Dio_A6,INPUT);break;
			case ADC_Channel7:Dio_SetChannelDirection(Dio_A7,INPUT);break;
		}
		ADC_GP2F_u16 = ADC_LP2F_u16;
		//ADC.ADCSRA.ADIF = HIGH;
		ADC.ADCSRA.ADSC = HIGH;
	}
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if (ADC_GP2F_u16!= NULL){
		//Disable ADC Interrupt
		ADC.ADCSRA.ADIF = LOW;
		// Calling Notification Function
		ADC_GP2F_u16(ADC.ADCHL);
	}
}
