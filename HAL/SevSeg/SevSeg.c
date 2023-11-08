#define F_CPU 16000000U
#include <util/delay.h>
#include "SevSeg.h"
Dio_ChannelType SevSeg_Data[4]={SevSeg_Data0,
								SevSeg_Data1,
								SevSeg_Data2,
								SevSeg_Data3};
Dio_ChannelType SevSeg_Select[4]={SevSeg_Select1,
								  SevSeg_Select2,
								  SevSeg_Select3,
								  SevSeg_Select4};
								  
void sevSegDisplay (u8 Data)
{
	for (int i=0;i<4;i++)
		Dio_WriteChannel(SevSeg_Data[i],GET_BIT(Data,i));
}

void sevSegDisplayAll(u16 Data)
{
	u8 disp =0b00000001;
	u8 arr[4] = 
	{(Data%10),(((Data%100)-(Data%10))/10),(((Data%1000)-(Data%100))/100),(((Data%10000)-(Data%1000))/1000)};
	for (int i = 0 ; i<4 ;i++)
	{
		for (u8 j =0 ;j<4;j++)
			Dio_WriteChannel(SevSeg_Select[j],(!GET_BIT(disp,j)));
		sevSegDisplay(arr[i]);
		disp<<=1;
		_delay_ms(5);
	}
}

void svnSegDisp_Dms(u16 Data, u16 Delay)
{
	for (u16 i =0 ; i<Delay ;i++)
	{
		sevSegDisplayAll(Data);
		_delay_ms(1);	
	}
	
}