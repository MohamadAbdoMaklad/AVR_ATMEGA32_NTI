#include "DIO.h"
void Dio_SetChannelDirection(Dio_ChannelType ChannelId , Dio_DirectionTypes Direction)
{
	MOD_REG_BITS(DIO.PORT[ChannelId/8].DDR,1,ChannelId%8,Direction);
}
void Dio_WriteChannel(Dio_ChannelType ChannelId , Dio_LevelType Level)
{
	MOD_REG_BITS(DIO.PORT[ChannelId/8].PORT,1,ChannelId%8,Level);
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	return GET_BIT(DIO.PORT[ChannelId/8].PIN,(ChannelId%8));
}

void Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	TOGGLE_BIT(DIO.PORT[ChannelId/8].PORT,ChannelId%8);
}

