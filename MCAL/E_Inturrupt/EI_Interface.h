#ifndef EI_INTERFACE_H_
#define EI_INTERFACE_H_

typedef enum
{
	EI_INT2=5,
	EI_INT0=6,
	EI_INT1=7,
}EI_Source_t;
typedef enum
{
	LOW_LEVEL=0,
	BOTH_EDGES,
	FALLING_EDGE,
	RISING_EDGE
}SNC_Mode_t;

void EI_voidInit(EI_Source_t copy_IntNo,STATE_t copy_STATE);
STATE_t EI_stateGetIEFlagState(EI_Source_t copy_IntNo);
void EI_voidSNCONTROLE_MODE(EI_Source_t copy_IntNo,SNC_Mode_t copy_MODE);
void EI_voidSetCallBack(EI_Source_t copy_IntNo,v_P2F_v EI_Func_PTR);



#endif /* EI_INTERFACE_H_ */