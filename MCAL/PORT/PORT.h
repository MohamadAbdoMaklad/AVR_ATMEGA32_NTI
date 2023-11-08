#ifndef PORT_H_
#define PORT_H_

#include "DIO.h"

typedef struct{
	Dio_ChannelType PinID;
	Dio_DirectionTypes Direction;
}Dio_PinConfig;

#define PINCOUNT 33
void Port_Init (void);

#endif