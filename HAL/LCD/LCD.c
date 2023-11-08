#define F_CPU 16000000UL
#include <util/delay.h>
#include "DIO.h"
#include "PORT.h"
#include "LCD.h"

Dio_ChannelType LCD_DataPinsArr[4]={Data0,Data1,Data2,Data3};

void LCD_Init(void)
{
	Dio_SetChannelDirection(Data0,OUTPUT);
	Dio_SetChannelDirection(Data1,OUTPUT);
	Dio_SetChannelDirection(Data2,OUTPUT);
	Dio_SetChannelDirection(Data3,OUTPUT);
	Dio_SetChannelDirection(LCD_RS,OUTPUT);
	Dio_SetChannelDirection(LCD_E,OUTPUT);
	
	Dio_WriteChannel(LCD_E,STD_HIGH);
	
	_delay_ms(20);
	LCD_Cmd(0x02);
	LCD_Cmd(0x28);
	LCD_Cmd(0x0C);		//Set Function 4Bit - 2Line - 5*8
	LCD_Cmd(0x06);		//Entry Mode Move Right
	LCD_Cmd(0x01);		//Display ON & courser OFF & No Blinking
	_delay_ms(2);
}
void LCD_Enable(void)
{
	Dio_WriteChannel(LCD_E,STD_LOW);
	_delay_us(1);
	Dio_WriteChannel(LCD_E,STD_HIGH);
}
void LCD_Cmd(u8 Cmd)
{
	Dio_WriteChannel(LCD_RS,STD_LOW);
	/*for (u8 i = 0 ;i<4 ; i++)
	{
		Dio_WriteChannel(LCD_DataPinsArr[i],GET_BIT(Cmd,i));
	}*/
	Dio_WriteChannel(LCD_DataPinsArr[0],GET_BIT(Cmd,4));
	Dio_WriteChannel(LCD_DataPinsArr[1],GET_BIT(Cmd,5));
	Dio_WriteChannel(LCD_DataPinsArr[2],GET_BIT(Cmd,6));
	Dio_WriteChannel(LCD_DataPinsArr[3],GET_BIT(Cmd,7));
	
	LCD_Enable();
	_delay_us(200);
	/*for (u8 i = 0 ;i<4 ; i++)
	{
		Dio_WriteChannel(LCD_DataPinsArr[i],GET_BIT(Cmd,(i+4)));
	}*/
	Dio_WriteChannel(LCD_DataPinsArr[0],GET_BIT(Cmd,0));
	Dio_WriteChannel(LCD_DataPinsArr[1],GET_BIT(Cmd,1));
	Dio_WriteChannel(LCD_DataPinsArr[2],GET_BIT(Cmd,2));
	Dio_WriteChannel(LCD_DataPinsArr[3],GET_BIT(Cmd,3));
	LCD_Enable();
	_delay_ms(2);
}
void LCD_Char(s8 Data)
{
	Dio_WriteChannel(LCD_RS,STD_HIGH);
	/*for (u8 i = 0 ;i<4 ; i++)
	{
		Dio_WriteChannel(LCD_DataPinsArr[i],GET_BIT(Cmd,i));
	}*/
	Dio_WriteChannel(LCD_DataPinsArr[0],GET_BIT(Data,4));
	Dio_WriteChannel(LCD_DataPinsArr[1],GET_BIT(Data,5));
	Dio_WriteChannel(LCD_DataPinsArr[2],GET_BIT(Data,6));
	Dio_WriteChannel(LCD_DataPinsArr[3],GET_BIT(Data,7));
	
	LCD_Enable();
	_delay_us(200);
	/*for (u8 i = 0 ;i<4 ; i++)
	{
		Dio_WriteChannel(LCD_DataPinsArr[i],GET_BIT(Cmd,(i+4)));
	}*/
	Dio_WriteChannel(LCD_DataPinsArr[0],GET_BIT(Data,0));
	Dio_WriteChannel(LCD_DataPinsArr[1],GET_BIT(Data,1));
	Dio_WriteChannel(LCD_DataPinsArr[2],GET_BIT(Data,2));
	Dio_WriteChannel(LCD_DataPinsArr[3],GET_BIT(Data,3));
	LCD_Enable();
	_delay_ms(2);
}
void LCD_String(s8 * String)
{
	u8 i;
	for (i=0;String[i] != '\0';i++)
	LCD_Char(String[i]);
}
void LCD_SetPosition(u8 LineNo, u8 Position)
{
	switch (Position)
	{
		case 0 ... 19 :
		{
			switch(LineNo)
			{
				case 1: LCD_Cmd((0x80 | (Position & 0xFF)));break;
				case 2: LCD_Cmd((0xC0 | (Position & 0xFF)));break;
				case 3: LCD_Cmd((0x94 | (Position & 0xFF)));break;
				case 4: LCD_Cmd((0xD4 | (Position & 0xFF)));break;
			}
		}break;
	}
	
}
void LCD_Clear(void)
{
	LCD_Cmd(0x01);
}
/*
void LCD_Custom_Char(Custom_Charactars Location,U8 * msg)
{
	if (Location<8)
	{
		LCD_Cmd((0x40 + (Location*8)));
		u8 i;
		for(i=0;i<8;i++)
		{
			LCD_Char(msg[i]);
		}
	}
}*/