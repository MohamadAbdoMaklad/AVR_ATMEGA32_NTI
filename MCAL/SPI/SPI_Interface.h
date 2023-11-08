#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_
#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"
#include "SPI_Private.h"
#define SPI_SS_Pin		Dio_B4
#define SPI_MOSI_Pin	Dio_B5
#define SPI_MISO_Pin	Dio_B6
#define SPI_SCK_Pin		Dio_B7

void SPI_voidInit(SPI_Inin_t *Options);
void SPI_voidTransieve(u8 copy_u8TXData,u8* copy_AddRXData);
void SPI_voidTransmitAssynchronous(u8 copy_u8TXData , v_P2F_u8 SPI_LP2F_u8);

#endif /* SPI_INTERFACE_H_ */