#include <stdio.h>
#include "DIO.h"
#include "PORT.h"

extern Dio_PinConfig PinConfig[];

void Port_Init()
{
	for (u8 Count = 0; Count < PINCOUNT; Count++)
	{
		if (PinConfig[Count].PinID == Dio_PinMax)
		{
			break;
		}
		MOD_REG_BITS(DIO.PORT[PinConfig[Count].PinID/8].DDR ,1,PinConfig[Count].PinID%8,PinConfig[Count].Direction);
	}
}
