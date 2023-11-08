/*
 * TWI_interface.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Kareem Hussein
 */

#ifndef MCAL_TWI_INCLUDES_TWI_INTERFACE_H_
#define MCAL_TWI_INCLUDES_TWI_INTERFACE_H_

#include "LIB_STD.h"
void TWI_voidInitMAster           (u8 Copy_u8Add);
void TWI_voidSendStartCondition   (void);
void TWI_voidSendRepetedStart(void);
void TWI_voidSendStoptCondition    (void);
void TWI_voidSendSlaveAddress_WriteRequist(u8 Copy_u8SlaveAdd);
void TWI_voidSendSlaveAddress_ReadRequist (u8 Copy_u8SlaveAdd);
void TWI_voidMaster_WriteDataByte  (u8 Copy_u8TxData);
void TWI_voidMaster_ReadDataByte   (u8* Copy_pu8RxData);    



#endif /* MCAL_TWI_INCLUDES_TWI_INTERFACE_H_ */
