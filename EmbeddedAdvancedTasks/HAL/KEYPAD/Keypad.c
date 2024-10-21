#include "StdTypes.h"

#include "DIO_Interface.h"

#include "Keypad_Interface.h"
#include "Keypad_Cfg.h"
#include "KeyPad_Private.h"


void Keypad_Init(void)
{
	for(u8 r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
}
u8 KEYPAD_GetKey(void)
{
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				key=KeysArray[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	return key;
}