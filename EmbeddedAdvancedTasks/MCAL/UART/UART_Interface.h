

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_Init(u16 BaudRate);
void UART_SendBusyWait(u8 Copy_u8DataByte);
u8 UART_ReceiveBusyWait(void);
void UART_SendNoBlock(u8 data);
u8 UART_ReceiveNoBlock(void);
void UART_TXInterruptEnable(void);
void UART_TXInterruptDisable(void);
void UART_RXInterruptEnable(void);
void UART_RXInterruptDisable(void);



#endif /* UART_INTERFACE_H_ */