#ifndef SEVSEG_H_
#define SEVSEG_H_
#include "LIB_BIT_MATH.h"
#include "LIB_STD.h"
#include "DIO.h"
#include "PORT.h"
#define SevSeg_Data0	Dio_B0
#define SevSeg_Data1	Dio_B1
#define SevSeg_Data2	Dio_B2
#define SevSeg_Data3	Dio_B4

#define SevSeg_Select1	Dio_A3
#define SevSeg_Select2	Dio_A2
#define SevSeg_Select3	Dio_B5
#define SevSeg_Select4	Dio_B6

void sevSegDisplay (u8 Data);
void sevSegDisplayAll(u16 Data);
void svnSegDisp_Dms(u16 Data, u16 Delay);
#endif /* SEVSEG_H_ */