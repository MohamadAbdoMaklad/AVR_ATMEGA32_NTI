/*
 * DCM_Interface.h
 *
 * Created: 28/10/2023 9:26:41 PM
 *  Author: moham
 */ 


#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_


#define DCM_CLOCK_WISE                   1
#define DCM_COUNTER_CLOCK_WISE           2

typedef enum
{
	DCM_CW = 0,
	DCM_CCW
	}DCM_Direction_t;

void DCM_Init(void);
void DCM_voidOn(DCM_Direction_t Copy_Direction);
void DCM_voidControlSpeed(u8 Copy_u8Speed);
void DCM_voidOff(void);


#endif /* DCM_INTERFACE_H_ */