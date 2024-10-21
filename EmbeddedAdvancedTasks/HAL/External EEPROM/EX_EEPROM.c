#include "StdTypes.h"

#include "TWI_Interface.h"

#include "EX_EEPROM_Interface.h"
#include "EX_EEPROM_Private.h"
#include "EX_EEPROM_Cfg.h"

#include "LCD_Interface.h"

void Ex_EEPROMInit(void);
TWI_ErrStatus EX_EEPROMWriteData(u16 Copy_u16Address,u8 Copy_u8DataByte)
{
	u8 x=0;
	LCD_SetCurser(0,0);
	LCD_WriteNumber(x);
	LCD_Init();
	TWI_ErrStatus Local_ErrStatus=NoError;
	if(TWI_SendStartCondition()==NoError)
	{
		x++;
		LCD_SetCurser(0,0);
		LCD_WriteNumber(x);
		//(10100000|0<<2|(Copy_u16Address>>8))
		//((0XA0)|(0<<2)|(Copy_u16Address>>8)
		//((0XA0)|(0<<2)|(Copy_u16Address>>8))
		if(TWI_SendSlaveAddressWithWrite((u8)((0x0A)|((Copy_u16Address&0x0700)>>7)))==NoError)
		{
			x++;
			LCD_SetCurser(0,0);
			LCD_WriteNumber(x);
			if(TWI_MasterWriteDataByte((u8)Copy_u16Address)==NoError)
			{
				x++;
				LCD_SetCurser(0,0);
				LCD_WriteNumber(x);
				if(TWI_MasterWriteDataByte(Copy_u8DataByte)==NoError)
				{
					x++;
					LCD_SetCurser(0,0);
					LCD_WriteNumber(x);
					TWI_SendStopCondition();
				}
				else
				{
					Local_ErrStatus=MasterWriteByteErr;
				}
			}
			else
			{
				Local_ErrStatus=MasterWriteByteErr;
			}
		}
		else
		{
			LCD_SetCurser(1,0);
			LCD_WriteNumber(6);
			Local_ErrStatus=SlaveAddressWithWriteErr;
		}
	}
	else
	{
		Local_ErrStatus=StartCondionErr;
	}
}
void EX_EEPROMReadData(u16 Copy_u16Address,u8*Copy_u8DataByte)
{
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite(((0XA0)|(0<<2)|(Copy_u16Address>>8)));
	TWI_MasterWriteDataByte((u8)Copy_u16Address);
	TWI_SendRepeatedStart();
	TWI_SendSlaveAddressWithRead(Copy_u16Address);
	TWI_MasterReadDataByte(Copy_u8DataByte);
	TWI_SendStopCondition();
}