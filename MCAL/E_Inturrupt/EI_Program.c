#include "LIB_STD.h"
#include "LIB_BIT_MATH.h"

#include "EI_Private.h"
#include "EI_Interface.h"

static v_P2F_v EI_CBF_Arr[3]={NULL};

void EI_voidInit(EI_Source_t copy_IntNo,STATE_t copy_STATE)
{
	MOD_BIT(EI_GICR_Register,copy_IntNo,copy_STATE);
}
STATE_t EI_stateGetIEFlagState(EI_Source_t copy_IntNo)
{
	return GET_BIT(EI_GICR_Register,copy_IntNo);
}
void EI_voidSNCONTROLE_MODE(EI_Source_t copy_IntNo,SNC_Mode_t copy_MODE)
{
	switch(copy_IntNo)
	{
		case EI_INT0:MOD_REG_BITS(EI_MCUCR_Register,2,0,copy_MODE);break;
		case EI_INT1:MOD_REG_BITS(EI_MCUCR_Register,2,2,copy_MODE);break;
		case EI_INT2:MOD_BIT(EI_MCUCSR_Register,6,GET_BIT(copy_MODE,0));break;
	}	
}
void EI_voidSetCallBack(EI_Source_t copy_IntNo,v_P2F_v EI_Func_PTR)
{
	switch(copy_IntNo)
	{
		case EI_INT0:EI_CBF_Arr[0] = EI_Func_PTR;break;
		case EI_INT1:EI_CBF_Arr[1] = EI_Func_PTR;break;
		case EI_INT2:EI_CBF_Arr[2] = EI_Func_PTR;break;
	}
}

/*
ISR (INT0_vect)
{
	if (EXT_INTERRUPT0_FUNCTION_PTR() != NULL)
		EXT_INTERRUPT0_FUNCTION_PTR();
}
ISR (INT1_vect)
{
	if (EXT_INTERRUPT1_FUNCTION_PTR() != NULL)
		EXT_INTERRUPT1_FUNCTION_PTR();
}
ISR (INT2_vect)
{
	if (EXT_INTERRUPT2_FUNCTION_PTR() != NULL)
		EXT_INTERRUPT2_FUNCTION_PTR();
}
*/

void __vector_1(void) __attribute__ ((signal));
void __vector_1(void)
{
	if (EI_CBF_Arr[0] != NULL)
	{
		EI_CBF_Arr[0]();
	}
}

void __vector_2(void) __attribute__ ((signal));
void __vector_2(void)
{
	if (EI_CBF_Arr[1] != NULL)
	{
		EI_CBF_Arr[1]();
	}
}


void __vector_3(void) __attribute__ ((signal));
void __vector_3(void)
{
	if (EI_CBF_Arr[2] != NULL)
	{
		EI_CBF_Arr[2]();
	}
		
}