#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "SPI_Cfg.h"


static void (*SPI_Fptr)(void)=NULLPTR;


/***********************Configuration************************************************/
/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output 
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/

void SPI_Init(void)
{
		
    /************************** SPCR Description **************************
     * SPIE    = 0 Disable SPI Interrupt
     * SPE     = 1 Enable SPI Driver
     * DORD    = 0 Transmit the MSB first
     * MSTR    = 1 Enable Master
     * CPOL    = 0 SCK is low when idle
     * CPHA    = 0 Sample Data with the raising edge
     * SPR1:0  = 00 Choose SPI clock = Fosc/4
     ***********************************************************************/
	/* Master or Slave */
	#if SPI_MPDE==MASTER
	SET_BIT(SPCR,MSTR);
	#elif SPI_MPDE==SLAVE
	CLR_BIT(SPCR,MSTR);
	#endif
	/*Clock is must in MASTER mode only 
	 *Choose SPI clock = Fosc/4 
	 * Clear the SPI2X bit in SPSR to Choose SPI clock = Fosc/4 */
	#if SPI_MPDE==MASTER
	SPSR&=~(1<<SPI2X);
	#endif
	/*SPI Enable*/
	SET_BIT(SPCR,SPE);
}

u8 SPI_sendReceiveByte(u8 data)
{
	/* Initiate the communication and send data by SPI */
	SPDR=data;
	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while(!READ_BIT(SPSR,SPIF));
	/*
	 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	return SPDR;
}

u8 SPI_ReceivePeriodic(u8*Pdata)
{
	if(READ_BIT(SPSR,SPIF))
	{
		*Pdata=SPDR;
		return 1;
	}
	return 0;
}

void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}
u8 SPI_ReceiveNoBlock(void)
{
	return SPDR;
}
void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}
void SPI_InterruptDisable(void)
{
	CLR_BIT(SPCR,SPIE);
}
void SPI_SetCallBack(void(*LocalFptr)(void))
{
	SPI_Fptr=LocalFptr;
}

ISR(SPI_STC_vect)
{
	if(SPI_Fptr!=NULLPTR)
	{
		SPI_Fptr();
	}
}

/*********************Function in Services**************************/
void SPI_SendString(u8*SendStr,u8*ReceiveStr)
{
	u8 i;
	for(i=0;SendStr[i];i++)
	{
		ReceiveStr[i]=SPI_sendReceiveByte(SendStr[i]);
	}
	ReceiveStr[i]=0;
	SPI_sendReceiveByte(0);
}