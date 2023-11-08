#ifndef LCD_H_
#define LCD_H_
#include "DIO.h"
#include "PORT.h"



#define LCD_RS	Dio_A3
//#define LCD_RW	Dio_A0
#define LCD_E	Dio_A2

#define Data0	Dio_B0
#define Data1	Dio_B1
#define Data2	Dio_B2
#define Data3	Dio_B4

void LCD_Init(void);
void LCD_Enable(void);
void LCD_Cmd(u8 Cmd);
void LCD_Char(s8 Data);
void LCD_String(s8 * String);
void LCD_SetPosition(u8 LineNo, u8 Position);
void LCD_Clear(void);
//void LCD_Custom_Char(Custom_Charactars Location,U8 * msg);



#endif /* LCD_H_ */