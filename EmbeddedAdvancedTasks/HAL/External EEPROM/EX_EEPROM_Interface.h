
#ifndef EX_EEPROM_INTERFACE_H_
#define EX_EEPROM_INTERFACE_H_

void Ex_EEPROMInit(void);
TWI_ErrStatus EX_EEPROMWriteData(u16 Copy_u16Address,u8 Copy_u8DataByte);
void EX_EEPROMReadData(u16 Copy_u16Address,u8*Copy_u8DataByte);


#endif /* EX_EEPROM_INTERFACE_H_ */