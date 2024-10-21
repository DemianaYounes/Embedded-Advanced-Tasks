#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Cfg.h"


static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;

void UART_Init(u16 BaudRate)
{
	u16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed
	 * U2X = 0 for Normal transmission speed*/
	UCSRA = ((1<<U2X)&0xfd);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/ 
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/ 	
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1); 
	
	/* Calculate the UBRR register value */
	ubrr_value = (u16)((((u32)8000000 / ((u32)BaudRate * 16))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}
void UART_SendBusyWait(u8 Copy_u8DataByte)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=Copy_u8DataByte;
}
u8 UART_ReceiveBusyWait(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}

void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}

/*************************************Interrupt_Enable*******************************************/
void UART_TXInterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}
void UART_TXInterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RXInterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}
void UART_RXInterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

/***********************SET Call Back********************************/
void  UART_TXCallBack(void(*LocalPtr)(void))
{
	UART_TX_Fptr=LocalPtr;
}

void  UART_RXCallBack(void(*LocalPtr)(void))
{
	UART_RX_Fptr=LocalPtr;
}

/************************************ISR************************************/
ISR(UART_TX_vect)
{
	if(UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}

ISR(UART_RX_vect)
{
	if(UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}