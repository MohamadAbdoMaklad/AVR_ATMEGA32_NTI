/*
 * TWI_private.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Kareem Hussein
 */

#ifndef MCAL_TWI_INCLUDES_TWI_PRIVATE_H_
#define MCAL_TWI_INCLUDES_TWI_PRIVATE_H_


#define TWI_STATUS_VALUE                    (TWSR&0xF8)
									       
#define TWI_START_CONDITION_ACK             0x08
#define TWI_REP_START_CONDITION_ACK         0x10
#define TWI_SLAVE_ADDRESS_WRITE_ACK         0x18
#define TWI_SLAVE_ADDRESS_READ_ACK          0x40
#define TWI_MASTER_DATA_TRANSMIT_ACK        0x28
#define TWI_MASTER_DATA_RECIEVE_ACK         0x50

#endif /* MCAL_TWI_INCLUDES_TWI_PRIVATE_H_ */
