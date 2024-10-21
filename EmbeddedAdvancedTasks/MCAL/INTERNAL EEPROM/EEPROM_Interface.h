

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

typedef enum{
	FALSE,
	TRUE
	}bool_t;

void EEPROM_Init(void);
void EEPROM_write(u16 Copy_u16Address, u8 Copy_u8Data);
u8 EEPROM_read(u16 Copy_u16Address);
void EEPROM_EnableInterrupt(void);
void EEPROM_DisableInterrupt(void);
u8 EEPROM_WriteDataInterrupt(u16 Copy_u16Address, u8 Copy_u8Data);
void EEPROM_SetCallBack(void(*LocalFptr)(void));


#endif /* EEPROM_INTERFACE_H_ */