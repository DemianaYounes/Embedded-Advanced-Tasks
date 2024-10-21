


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_Init(void);
u8 SPI_sendReceiveByte(u8 data);
u8 SPI_ReceivePeriodic(u8*Pdata);
void SPI_SendNoBlock(u8 data);
u8 SPI_ReceiveNoBlock(void);
void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);
void SPI_SetCallBack(void(*LocalFptr)(void));



#endif /* SPI_INTERFACE_H_ */