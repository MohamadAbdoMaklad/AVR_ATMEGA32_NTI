#ifndef DIO_H_
#define DIO_H_
#include "LIB_STD.h"
#include "LIB_BIT_MATH.h"
#include "DIO.h"

typedef struct
{
	volatile u8 PIN;
	volatile u8 DDR;
	volatile u8 PORT;
	}Port_t;
typedef struct
{
	Port_t PORT[4];
	}DioRig_t;
#define DIO (*(volatile DioRig_t*)0x30)
typedef enum{
	Dio_D0 = 0,
	Dio_D1,
	Dio_D2,
	Dio_D3,
	Dio_D4,
	Dio_D5,
	Dio_D6,
	Dio_D7,
	
	Dio_C0,
	Dio_C1,
	Dio_C2,
	Dio_C3,
	Dio_C4,
	Dio_C5,
	Dio_C6,
	Dio_C7,
	
	Dio_B0,
	Dio_B1,
	Dio_B2,
	Dio_B3,
	Dio_B4,
	Dio_B5,
	Dio_B6,
	Dio_B7,
	
	Dio_A0,
	Dio_A1,
	Dio_A2,
	Dio_A3,
	Dio_A4,
	Dio_A5,
	Dio_A6,
	Dio_A7,
	Dio_PinMax,
}Dio_ChannelType;

typedef enum{
	Dio_PortD = 0,
	Dio_PortC,
	Dio_PortB,
	Dio_PortA,
	Dio_PortMax,
}Dio_PortType;

typedef enum{
	INPUT = 0,
	OUTPUT = 1,
}Dio_DirectionTypes;
typedef enum{
	STD_LOW = 0,
	STD_HIGH = 1,
}Dio_LevelType;

void Dio_SetChannelDirection(Dio_ChannelType ChannelId , Dio_DirectionTypes Direction);
void Dio_WriteChannel(Dio_ChannelType ChannelId , Dio_LevelType Level);
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_FlipChannel(Dio_ChannelType ChannelId);



#endif /* DIO_H_ */