/*
 * TWI_register.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Kareem Hussein
 */

#ifndef MCAL_TWI_INCLUDES_TWI_REGISTER_H_
#define MCAL_TWI_INCLUDES_TWI_REGISTER_H_


                              /* TWI REGISTERS */

// TWI Bit Rate Register
#define TWBR         (*(volatile u8*)0x20)

// TWI Control Register
#define TWCR         (*(volatile u8*)0x56)
#define TWIE         0
#define TWEN         2
#define TWWC         3
#define TWSTO        4
#define TWSTA        5
#define TWEA         6
#define TWINT        7


// TWI Status Register
#define TWSR         (*(volatile u8*)0x21)
#define TWPS0        0
#define TWPS1        1

// TWI Data Register
#define TWDR         (*(volatile u8*)0x23)

// TWI (Slave) Address Register
#define TWAR         (*(volatile u8*)0x22)
#define TWGCE        0


#endif /* MCAL_TWI_INCLUDES_TWI_REGISTER_H_ */
