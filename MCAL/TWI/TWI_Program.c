/*
 * TWI_program.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Kareem Hussein
 */


/* UTILES_LIB */
#include "LIB_STD.h"
#include "LIB_BIT_MATH.h"

/* MCAL */
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"


void TWI_voidInitMAster(u8 Copy_u8Add)
{
	if((Copy_u8Add<128)&&(Copy_u8Add>0))
	{
		TWAR = Copy_u8Add<<1;
	}

	// Set Prescaller = 1 >> Set Freq. = 400KHZ
	TWBR = 12;
	CLEAR_BIT(TWSR,TWPS0);
	CLEAR_BIT(TWSR,TWPS1);

	// Enable ACK
	SET_BIT(TWCR,TWEA);

	// Enable TWI peripheral
	SET_BIT(TWCR,TWEN);
}


void TWI_voidSendStartCondition(void)
{
	// Request Start Condition
	SET_BIT(TWCR,TWSTA);

	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);

	// Busy Wait for the flag
	while(0 == GET_BIT(TWCR,TWINT));

	// Check ACK = SC ACK
	while(TWI_STATUS_VALUE != TWI_START_CONDITION_ACK);
}


void TWI_voidSendRepetedStart(void)
{
	// Request Start Condition
	SET_BIT(TWCR,TWSTA);

	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);

	// Busy Wait for the flag
	while(0 == GET_BIT(TWCR,TWINT));

	// Check ACK = Repeated SC ACK
	while(TWI_STATUS_VALUE != TWI_REP_START_CONDITION_ACK);
}


void TWI_voidSendStoptCondition(void)
{
	// Request Stop Condition
	SET_BIT(TWCR,TWSTO);

	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);
}


void TWI_voidSendSlaveAddress_WriteRequist(u8 Copy_u8SlaveAdd)
{
	if(Copy_u8SlaveAdd<128)
	{
		TWDR = Copy_u8SlaveAdd<<1;

		// Select write operation
		CLEAR_BIT(TWDR,0);
		// Clear Start Condition bit
		CLEAR_BIT(TWCR,TWSTA);

		// Clear flag to start current job
		SET_BIT(TWCR,TWINT);

		// Busy Wait for the flag
		while(0 == GET_BIT(TWCR,TWINT));

		// Check ACK = Master transmit ( slave address + Write request ) ACK
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_WRITE_ACK);
	}
}


void TWI_voidSendSlaveAddress_ReadRequist(u8 Copy_u8SlaveAdd)
{
	if(Copy_u8SlaveAdd<128)
	{
		TWDR = Copy_u8SlaveAdd<<1;

		// Select read operation
		SET_BIT(TWDR,0);

		// Clear Start Condition bit
		CLEAR_BIT(TWCR,TWSTA);

		// Clear flag to start current job
		SET_BIT(TWCR,TWINT);

		// Busy Wait for the flag
		while(0 == GET_BIT(TWCR,TWINT));

		// Check ACK = Master transmit ( slave address + Read request ) ACK
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_READ_ACK);
	}
}


void TWI_voidMaster_WriteDataByte(u8 Copy_u8TxData)
{
	TWDR = Copy_u8TxData;
	
	// Clear flag to start current job
    SET_BIT(TWCR,TWINT);
	
	// Busy Wait for the flag
	while(0 == GET_BIT(TWCR,TWINT));
	
	// Check ACK = Master transmit data ACK
	while(TWI_STATUS_VALUE != TWI_MASTER_DATA_TRANSMIT_ACK);
}


void TWI_voidMaster_ReadDataByte(u8* Copy_pu8RxData)
{
	if(Copy_pu8RxData != NULL)
	{
		// Clear flag to start current job
        SET_BIT(TWCR,TWINT);
	
	    // Busy Wait for the flag
	    while(0 == GET_BIT(TWCR,TWINT));
	    
	    // Check ACK = Master received data with ACK
	    while(TWI_STATUS_VALUE != TWI_MASTER_DATA_RECIEVE_ACK);
		
		// Read Data from data register
		*Copy_pu8RxData = TWDR;
	}
}


