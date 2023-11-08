/*
 * UART.h
 *
 * Created: 28/10/2023 1:51:57 PM
 *  Author: moham
 */ 


#ifndef UART_H_
#define UART_H_


#include "UART_Types.h"
#include "UART_Registers.h"
//#include "Clock.h"
void UART_Init(UART_Init_Types * Options);
void UART_Transmet(u8 Data);
void UART_TransmetString(s8 * String);
u8 UART_ReceiveWithTimeOut(u32 time);
u8 UART_Receive(void);
//s8 UART_ReceiveString(s8 * String,u8 Size);


#endif /* UART_H_ */