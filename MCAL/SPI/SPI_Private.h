#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


typedef enum
{
	/*CPOL -- CPHA*/
	Mode0_00 =0,
	Mode1_01 =1,
	Mode2_10 =2,
	Mode3_11 =3
}CPOLCPHAS_t;

typedef enum
{
	/*CPOL -- CPHA*/
	Fcpu_4	=0,
	Fcpu_16 =1,
	Fcpu_64 =2,
	Fcpu_128=3
}ClkPrescaler_t;

typedef enum
{
	SPI2X_OFF = 0,
	SPI2X_ON
}DoupleSpeedMode_t;

typedef enum
{
	SPI_Int_Disable = 0,
	SPI_Int_Enable = 1
}SPI_Interrupt_Mode_t;

typedef enum
{
	SPI_MSB = 0,
	SPI_LSB
}SPI_DataOrder_t;

typedef enum
{
	SPI_MASTER = 0,
	SPI_SLAVE
}SPI_MSSelect_t;

typedef struct
{
	u8 SPR  :2;
	u8 CPHAO:2;
	u8 MSTR :1;
	u8 DORD :1;
	u8 SPE  :1;
	u8 SPIE :1;
	}SPI_SPCR_t;
typedef struct
{
	u8 SPI2X:1;
	u8		:5;
	u8 WCOL :1;
	u8 SPIF :1;
}SPI_SPSR_t;

typedef struct
{
	SPI_SPCR_t SPCR;
	SPI_SPSR_t SPSR;
	u8 SPDR;
	}SPI_REG_t;
#define SPI	(*(volatile SPI_REG_t*)0x2D)

typedef struct
{
	SPI_MSSelect_t Mode;
	SPI_DataOrder_t DataOrder;
	SPI_Interrupt_Mode_t IntMode;
	DoupleSpeedMode_t DoupleSpeedMode;
	ClkPrescaler_t Prescaler;
	CPOLCPHAS_t CPOLCPHAS;
	}SPI_Inin_t;

#endif /* SPI_PRIVATE_H_ */