/************************************************/
/*Author	            : Mohamad Abdo Maklad	*/
/*Date		            : 20-10-2023		 	*/
/*Last Modification	    : 				 		*/
/*Version	            : V01					*/
/************************************************/
/******(  Main File Test DIO  )******************/
/************************************************/
//#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"
#include "DIO.h"
#include "PORT.h"
//#include "SevSeg.h"
#include "LCD.h"
//#include "GI_Interface.h"
//#include "EI_Interface.h"
#include "Timer0_Interface.h"
#include "ADC_Interface.h"
#include "Kpad.h"
#include "UART.h"

#include "DCM_Interface.h"


int main()
{
	LCD_Init();
	LCD_Clear();
	//Kpad_Init();
	UART_Init_Types UARTOptions = {UART_Asynchronous_Operration,
									UART_Parit_Disable,
									UART_1_StopBit,
									UART_CharSize_8Bit,
									UART_TX_Enable,
									UART_RX_Enable,
									UART_DoubleSpeed_Enable,
									UART_BaudRate_9600};
		
	UART_Init(&UARTOptions);
	//s8 arr[8] = "Mohamad ";
	while(1)
	{
		
		u8 val = UART_Receive();
		/*u8 key = Kpad_GetKey();


		if(key){

			UART_Transmet(key);

			//LCD_Clear();
			LCD_SetPosition(1,0);
			LCD_Char(key);
*/

		//} 
		LCD_Clear();
		LCD_SetPosition(1,0);
		switch(val)
		{
			case '0':{UART_TransmetString("-----> 0 Received");break;}
			case '1':{UART_TransmetString("-----> 1 Received");break;}
			case '2':{UART_TransmetString("-----> 2 Received");break;}
			case '3':{UART_TransmetString("-----> 3 Received");break;}
			case '4':{UART_TransmetString("-----> 4 Received");break;}
			case '5':{UART_TransmetString("-----> 5 Received");break;}
			case '6':{UART_TransmetString("-----> 6 Received");break;}
			case '7':{UART_TransmetString("-----> 7 Received");break;}
			case '8':{UART_TransmetString("-----> 8 Received");break;}
			case '9':{UART_TransmetString("-----> 9 Received");break;}
		};
	}
}



/*

int main()
{
	//u8 threshold;
	//u8 valUnits=0,valTenth=0;
	Port_Init();
	LCD_Init();
/ *	LCD_Char('A');* /
/ *	LCD_String("Embinux");* /

	LCD_Clear();
	LCD_SetPosition(1,0);
	//T0_voidInit();
	//T0_voidStart();
	/ *LCD_Char('A');* /
	s8 str[4]={0};
	while(1)
	{
		
		
		for (u8 i = 0;i<3;i++)
		{
			s8 val = Kpad_GetKey();
			if(val == 'B')
			{
				break;
			}
			else
			{
				LCD_SetPosition(1,i);
				LCD_Char(val);
				str[i] = val;
			}
		}
	}
		LCD_SetPosition(2,0);
		LCD_String(str);
	return 0;
	}*/
// 		
// 		valTenth = Kpad_GetKey();
// 		while(valTenth){
// 			LCD_Char(valTenth);
// 			valTenth = (valTenth-41)*10;
// 			break;
// 		}
// 		LCD_SetPosition(1,1);
// 		valUnits = Kpad_GetKey();
// 		while(valUnits){
// 			LCD_Char(valUnits);
// 			valUnits = valUnits-41;
// 			break;
// 		}
// 		threshold = valTenth+valUnits;
// 		//if('B' == Kpad_GetKey()){
// 			LCD_SetPosition(2,0);
// 			u8 arr[2];
//			LCD_String(itoa(threshold,&arr,10));
// 			//break;
// 		//}
// 		
// 		
				

/*
int main()
{
	Port_Init();
	LCD_Init();
	ADC_InitTypes AdcOptions = {ADC_Prescaler128,ADC_Vref_Internal,FreeRunning};
	ADC_Init(&AdcOptions);
	
	LCD_Init();
	LCD_Clear();
	LCD_SetPosition(1,0);
	while(1)
	{
		u16 ReadVal =0;
		ReadVal = ADC_READ(ADC_Channel0);
		c
		LCD_SetPosition(1,0);
		LCD_String(itoa(ReadVal,&arr,10));
		_delay_ms(300);
		LCD_Clear();
	}
}
*/




/*
	int main()
	{
		Port_Init();
		LCD_Init();
		Kpad_Init();
		LCD_Clear();
		LCD_SetPosition(1,0);

		while(1)
		{
 			LCD_SetPosition(1,0);
			u8 key = Kpad_GetKey();
			if(key){
				lcd_char(key);
			}
			
			
			if(key == 'B')
			{
				
				LCD_Clear();
			}
		}
		

		
		return 0;
	}*/