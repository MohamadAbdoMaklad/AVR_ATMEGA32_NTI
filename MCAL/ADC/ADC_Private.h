#ifndef ADC_H_
#define ADC_H_


typedef struct 
{
	u8 MUX		:5;
	u8 ADLAR	:1;
	u8 REFS		:2;
}ADMUX_rt;

typedef struct
{
	u8 ADPS		:3;
	u8 ADIE		:1;
	u8 ADIF		:1;
	u8 ADATE	:1;
	u8 ADSC		:1;
	u8 ADEN		:1;
}ADCSRA_rt;

typedef struct
{
	u8			:5;
	u8 ADTS		:3;
}SFIOR_rt;

	
typedef struct
{
	
	u16 ADCHL;//24 // 25
	ADCSRA_rt ADCSRA;//26
	ADMUX_rt ADMUX;//27
	u8 Resesrvrd[40];
	SFIOR_rt SFIOR;//50
	}ADC_t;
#define ADC (*((volatile ADC_t*)0x24))

#endif /* ADC_H_ */