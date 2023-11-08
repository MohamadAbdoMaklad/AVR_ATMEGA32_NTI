#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum{
	ADC_Channel0=0,
	ADC_Channel1,
	ADC_Channel2,
	ADC_Channel3,
	ADC_Channel4,
	ADC_Channel5,
	ADC_Channel6,
	ADC_Channel7
}ADC_ChannelTypes;

typedef enum{
	ADC_Prescaler2=1,
	ADC_Prescaler4,
	ADC_Prescaler8,
	ADC_Prescaler16,
	ADC_Prescaler32,
	ADC_Prescaler64,
	ADC_Prescaler128
}ADC_PrescalerTypes;

typedef enum{
	ADC_Vref_Aref=0,
	ADC_Vref_Avcc=1,
	ADC_Vref_Internal=3
}ADC_VrefTypes;

typedef enum{
	FreeRunning=0,
	AnalogComparator,
	ExternalInterruptRequest0,
	Timer_Counter0CompareMatch,
	Timer_Counter0Overflow,
	Timer_Counter1CompareMatchB,
	Timer_Counter1Overflow,
	Timer_Counter1CaptureEvent
}ADC_AutoTriggerSource;


typedef struct{
	ADC_PrescalerTypes adcClock;
	ADC_VrefTypes adcVref;
	ADC_AutoTriggerSource AutoTrigSource;
}ADC_InitTypes;

void ADC_Init (ADC_InitTypes * OPTIONS);
u16 ADC_READ (ADC_ChannelTypes CHANNEL_NO);

void ADC_voidEnableInterrupt(void);
void ADC_voidDisableInterrupt(void);

void ADC_voidReadAssynchronous(ADC_ChannelTypes CHANNEL_NO , v_P2F_u16 ADC_LP2F_u16);
#endif /* ADC_INTERFACE_H_ */