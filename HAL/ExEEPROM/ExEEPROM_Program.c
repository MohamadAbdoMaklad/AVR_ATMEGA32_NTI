#define F_CPU 16000000UL
#include <util/delay.h>
#include "TWI_Interface.h"
#include "ExEEPROM_Interface.h"
void ExEEPROM_voidInit(void)
{
	TWI_voidInitMAster(255);
}
void ExEEPROM_voidWriteByte(u16 copy_u16EEPROM_Add,u8 copy_u8DataByte)
{
	//|0b       0|............1010|.............................000|
	//|don't care|	EEPROM Address|	Oared bits fore rest of address|
	u8 local_u8Add = ((copy_u16EEPROM_Add>>8) | 0b01010000);
	//Send Start condition
	TWI_voidSendStartCondition();
	//Dio_WriteChannel(Dio_A4,HIGH);
	//Send Slave Address with the rest of memory address
	TWI_voidSendSlaveAddress_WriteRequist(local_u8Add);
	//send first 8bit of memory address
	TWI_voidMaster_WriteDataByte((u8)copy_u16EEPROM_Add);
	//send data byte
	TWI_voidMaster_WriteDataByte(copy_u8DataByte);
	//Send stop condition
	TWI_voidSendStoptCondition();
	// Self-time write delay write cycle delay (5ms >> According to the DATASHEET)
	_delay_ms(5);
}
void ExEEPROM_voidReadByte(u16 copy_u16EEPROM_Add,u8* copy_pu8DataByte)
{
	if (copy_pu8DataByte != NULL)
	{
		//|0b       0|............1010|.............................000|
		//|don't care|	EEPROM Address|	Oared bits fore rest of address|
		u8 local_u8Add = ((copy_u16EEPROM_Add>>8) | 0b01010000);
		//Send Start condition
		TWI_voidSendStartCondition();
		//Send Slave Address with the rest of memory address
		TWI_voidSendSlaveAddress_WriteRequist(local_u8Add);
		//send first 8bit of memory address
		TWI_voidMaster_WriteDataByte((u8)copy_u16EEPROM_Add);
		//Repeated Start To Change Operation To Read
		TWI_voidSendRepetedStart();
		//Send Slave Address with the rest of memory address
		TWI_voidSendSlaveAddress_ReadRequist(local_u8Add);
		//Read Data Byte
		TWI_voidMaster_ReadDataByte(copy_pu8DataByte);
		//Send stop condition
		TWI_voidSendStoptCondition();
		// Self-time write delay write cycle delay (5ms >> According to the DATASHEET)
		_delay_ms(5);
	}

}