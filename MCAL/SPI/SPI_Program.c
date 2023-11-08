#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"

#include "DIO.h"

#include "SPI_Interface.h"
#include "SPI_Private.h"

/*
master  -  slave
F_CPU /16
Disable
LSB
Disable
11 
*/

static v_P2F_u8 SPI_GP2F_u8 = NULL;

void SPI_voidInit(SPI_Inin_t *Options)
{
	SPI.SPCR.MSTR = Options->Mode;
	SPI.SPCR.SPR = Options->Prescaler;
	SPI.SPSR.SPI2X = Options->DoupleSpeedMode;
	SPI.SPCR.DORD = Options->DataOrder;
	SPI.SPCR.SPIE = Options->IntMode;
	SPI.SPCR.CPHAO = Options->CPOLCPHAS;
	if (Options->Mode == SPI_MASTER)
	{
		Dio_SetChannelDirection(SPI_SCK_Pin,OUTPUT);
		Dio_SetChannelDirection(SPI_MOSI_Pin,OUTPUT);
		Dio_SetChannelDirection(SPI_MISO_Pin,INPUT);
		Dio_SetChannelDirection(SPI_SS_Pin,OUTPUT);
	}
	else if (Options->Mode == SPI_SLAVE)
	{
		Dio_SetChannelDirection(SPI_SCK_Pin,INPUT);
		Dio_SetChannelDirection(SPI_MOSI_Pin,INPUT);
		Dio_SetChannelDirection(SPI_MISO_Pin,OUTPUT);
		Dio_SetChannelDirection(SPI_SS_Pin,INPUT);
	}

	
	SPI.SPCR.SPE = HIGH;
	
	
	
}
void SPI_voidTransieve(u8 copy_u8TXData,u8* copy_AddRXData)
{
	while (1 == SPI.SPSR.WCOL);
	if (copy_AddRXData != NULL)
	{
		SPI.SPDR = copy_u8TXData;
		while(0 == SPI.SPSR.SPIF);
		*copy_AddRXData = SPI.SPDR;
	}
	
}
 
 void SPI_voidTransmitAssynchronous(u8 copy_u8TXData ,v_P2F_u8 SPI_LP2F_u8 )
 {
 	if (SPI_LP2F_u8 != NULL)
 	{
 		SPI.SPCR.SPIE = HIGH;
 		SPI_GP2F_u8 = SPI_LP2F_u8;
 		while (1 == SPI.SPSR.WCOL);
 		SPI.SPDR = copy_u8TXData;
 	}
 	
 }


void __vector_12(void) __attribute__ ((signal));
void __vector_12(void)
{
 	if (SPI_GP2F_u8!= NULL)
 	{
 		SPI_GP2F_u8(SPI.SPDR);
 	}
	
}