/*
 * DCM_program.c
 *
 * Created: 9/20/2023 11:55:54 AM
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"

/* MCAL */
#include "Timer0_Interface.h"

/* HAL */
#include "DCM_Cfg.h"
#include "DCM_Interface.h"

/*DC Motor Driver Drire*/
/*This function could be used incited of using PORT if not exist */
void DCM_Init()
{
	Dio_SetChannelDirection(ENA_Pin,OUTPUT);
	Dio_SetChannelDirection(PWM_Pin,OUTPUT);
	Dio_SetChannelDirection(DIR_Pin,OUTPUT);
	T0_voidInit();
}


void DCM_voidOn(DCM_Direction_t Copy_Direction)
{
	/* Turn DC motor on using H-Bridge
	 By Setting PWM, Dir and Enable pins with high
	 or Dir Low depend on Copy_u8Direction*/
	Dio_WriteChannel(ENA_Pin,STD_HIGH);
	Dio_WriteChannel(PWM_Pin,STD_HIGH);
	Dio_WriteChannel(DIR_Pin,Copy_Direction);
}


void DCM_voidControlSpeed(u8 Copy_u8Speed)
{
	T0_voidStart();
	T0_voidSetDytyCycle_PWM(Copy_u8Speed);
	/* Controlling DC motor speed using PWM
	mode from TMR0 by setting Duty Cycle*/
}


void DCM_voidOff(void)
{
	Dio_WriteChannel(ENA_Pin,STD_LOW);
	/* Turn DC motor off using H-Bridge
	   By Setting Enable pin with low */
}
