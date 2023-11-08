#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"
#include "DIO.h"
#include "PORT.h"
#include "Kpad.h"
#include "KpadCfg.h"
#define F_CPU 16000000UL
#include <util/delay.h>


Dio_ChannelType KeyPadRows[RowsNo] = {KP_R0,KP_R1,KP_R2,KP_R3};
Dio_ChannelType KeyPadColoms[ColomsNo] = {KP_C0,KP_C1,KP_C2,KP_C3};
u8 KeyPad[RowsNo][ColomsNo] = { {'7','8','9','/'},
								{'4','5','6','*'},
								{'1','2','3','-'},
								{'C','0','=','+'}};
/*
u8 KeyPad[RowsNo][ColomsNo] = { {7,8,9,'/'},
								{4,5,6,'*'},
								{1,2,3,'-'},
								{'C',0,'=','+'}};*/
/*u8 KeyPad[RowsNo][ColomsNo] = { {'1','2','3','A'},
								{'4','5','6','B'},
								{'7','8','9','C'},
								{'*','0','#','D'}};*/

void Kpad_Init(void)
{
	u8 i,j;
	for (i=0;i<ColomsNo;i++)
	{
		Dio_SetChannelDirection(KeyPadColoms[i],INPUT);
		Dio_WriteChannel(KeyPadColoms[i],STD_HIGH);
	}
	for (j=0;j<RowsNo;j++)
	{
		Dio_SetChannelDirection(KeyPadRows[j],OUTPUT);
		Dio_WriteChannel(KeyPadRows[j],STD_HIGH);
	}
}

u8 Kpad_GetKey(void)
{
	u8 i,j;
	for(i=0;i<RowsNo;i++)
	{
		Dio_WriteChannel(KeyPadRows[i],STD_LOW);
		for(j=0;j<ColomsNo;j++)
		{
			if(Dio_ReadChannel(KeyPadColoms[j]) == STD_LOW)
			{
				_delay_ms(50);
				while(Dio_ReadChannel(KeyPadColoms[j]) == STD_LOW);
				return KeyPad[i][j];
			}
		}
		Dio_WriteChannel(KeyPadRows[i],STD_HIGH);
	}
	return LOW;
}