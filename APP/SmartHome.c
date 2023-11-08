/************************************************/
/*Author	            : Mohamad Abdo Maklad	*/
/*Date		            : 20-10-2023		 	*/
/*Last Modification	    : 				 		*/
/*Version	            : V01					*/
/************************************************/
/******(  Main File Test DIO  )******************/
/************************************************/
// #include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"
#include "DIO.h"
#include "PORT.h"
// #include "SevSeg.h"
// #include "LCD.h"
#include "GI_Interface.h"
// #include "EI_Interface.h"
#include "Timer0_Interface.h"
#include "ADC_Interface.h"
// #include "Kpad.h"
#include "UART.h"
#include "DCM_Interface.h"
// #include "Timer1_Interface.h"
#include "SPI_Interface.h"
// #include "TWI_Interface.h"
// #include "ExEEPROM_Interface.h"
#include "ServoMotor_Interface.h"

// Proteus Config
/*
#define LED1PIN			Dio_C2
#define LED2PIN			Dio_C3
#define LED3PIN			Dio_B3
#define ADCLM35			Dio_A0
#define MOTDIR1Pin		Dio_C4
#define MOTDIR2Pin		Dio_C5
#define MOTEnabPin		Dio_C6
// Allarm
#define Allarm1Pin		Dio_C0
#define Allarm2Pin		Dio_C1*/

#define LED1PIN		Dio_A6
#define LED2PIN		Dio_A5
#define LED3PIN		Dio_B3
#define ADCLM35		Dio_A1
#define MOTDIR1Pin 	Dio_B5
#define MOTDIR2Pin 	Dio_A0
#define MOTEnabPin 	Dio_B6
#define Allarm1Pin 	Dio_B7
#define Allarm2Pin 	Dio_C6

void SpiInt(copy_TxData)
{
	if (copy_TxData == StartSystem)
	{
		SystemStateFlag = StartSystem;
		UserState = OutHome;
	}
	else if (copy_TxData == AllarmOn)
	{
		SystemStateFlag = AllarmOn;
	}
	else if (copy_TxData == AllarmOFF)
	{
		SystemStateFlag = AllarmOFF;
	}
}
typedef enum
{
	InitSystem = 0,
	StartSystem = 1,
	AllarmOn = 2,
	AllarmOFF = 3

} SystemState_t;
typedef enum
{
	InHome = 0,
	OutHome = 1
} UserState_t;

typedef enum
{
	LED1Tog = '0',
	LED2Tog = '1',
	LED3Up = '2',
	LED3Down = '3'
} TerminalData_t;

SystemState_t SystemStateFlag = InitSystem;
UserState_t UserState = OutHome;

int main()
{
	GI_voidEnable();
	UART_Init_Types UARTOptions = {UART_Asynchronous_Operration,
								   UART_Parit_Disable,
								   UART_1_StopBit,
								   UART_CharSize_8Bit,
								   UART_TX_Enable,
								   UART_RX_Enable,
								   UART_DoubleSpeed_Enable,
								   UART_BaudRate_9600};
	UART_Init(&UARTOptions);

	ADC_InitTypes AdcOptions = {ADC_Prescaler128,
								ADC_Vref_Aref,
								FreeRunning};
	ADC_Init(&AdcOptions);

	SPI_Inin_t SpiOptions = {SPI_SLAVE,
							 SPI_LSB,
							 SPI_Int_Enable,
							 SPI2X_OFF,
							 Fcpu_16,
							 Mode3_11};
	SPI_voidInit(&SpiOptions);

	T0_voidInit();

	ServoMotor_voidInit();

	u8 LedPwmVal = 0;
	Dio_SetChannelDirection(LED1PIN, OUTPUT);
	Dio_SetChannelDirection(LED2PIN, OUTPUT);
	Dio_SetChannelDirection(LED3PIN, OUTPUT);
	Dio_SetChannelDirection(ADCLM35, INPUT);
	Dio_SetChannelDirection(MOTDIR1Pin, OUTPUT);
	Dio_SetChannelDirection(MOTDIR2Pin, OUTPUT);
	Dio_SetChannelDirection(MOTEnabPin, OUTPUT);
	Dio_SetChannelDirection(Allarm1Pin, OUTPUT);
	Dio_SetChannelDirection(Allarm2Pin, OUTPUT);
	Dio_WriteChannel(MOTEnabPin, STD_LOW);
	Dio_WriteChannel(MOTDIR1Pin, STD_HIGH);
	Dio_WriteChannel(MOTDIR2Pin, STD_LOW);

	SPI_voidTransmitAssynchronous(50, SpiInt);
	while (1)
	{
		while (SystemStateFlag == StartSystem)
		{
			while (UserState == OutHome)
			{
				// Door Open - Delay 10 sec Door Close
				ServoMotor_SetAngle(90);
				_delay_ms(3000);
				ServoMotor_SetAngle(0);
				ServoMotor_Off();
				UserState = InHome;
				break;
			}
			while (UserState == InHome && (SystemStateFlag == StartSystem))
			{
				// ADC & temp
				u16 TempVal = 0;
				TempVal = (((ADC_READ(ADC_Channel0) * 500) / 1023));
				if (TempVal < 5)
				{ // off AC
					Dio_WriteChannel(MOTEnabPin, STD_LOW);
				}
				else if (TempVal > 10)
				{ // on AC
					Dio_WriteChannel(MOTEnabPin, STD_HIGH);
				}
				TerminalData_t TerminalData = UART_ReceiveWithTimeOut(5000);
				if (TerminalData == LED1Tog)
				{
					Dio_FlipChannel(LED1PIN);
				}
				if (TerminalData == LED2Tog)
				{
					Dio_FlipChannel(LED2PIN);
				}
				if (TerminalData == LED3Up)
				{
					if ((LedPwmVal >= 0) && (LedPwmVal <= 90))
					{
						LedPwmVal += 10;
					}
					T0_voidSetDytyCycle_PWM(LedPwmVal);
					T0_voidStart();
				}
				if (TerminalData == LED3Down)
				{
					if ((LedPwmVal <= 100) && (LedPwmVal >= 10))
					{
						LedPwmVal -= 10;
					}
					if (LedPwmVal == 10)
					{
						T0_voidStop();
					}
					else
					{
						T0_voidSetDytyCycle_PWM(LedPwmVal);
						T0_voidStart();
					}
				}
			}
		}
		while (SystemStateFlag == AllarmOn)
		{
			// Allarm On
			Dio_WriteChannel(Allarm1Pin, STD_HIGH);
			Dio_WriteChannel(Allarm2Pin, STD_HIGH);
		}
		if (SystemStateFlag == AllarmOFF)
		{
			// off allarm
			Dio_WriteChannel(Allarm1Pin, STD_LOW);
			Dio_WriteChannel(Allarm2Pin, STD_LOW);
			SystemStateFlag = StartSystem;
		}
	}
	return 0;
}