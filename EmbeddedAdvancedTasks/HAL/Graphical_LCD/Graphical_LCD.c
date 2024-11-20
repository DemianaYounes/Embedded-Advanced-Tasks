/*
 * Graphical_LCD.c
 *
 * Created: 11/3/2024 2:59:22 AM
 *  Author: Demiana Younes
 */ 

#define F_CPU  8000000
#include <util/delay.h>



#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"

#include "Graphical_LCD_Interface.h"
#include "Graphical_LCD_Private.h"
#include "Graphical_LCD_Config.h"

void GLCD_voidInit()
{
	DIO_WritePin(GLCD_CS1,HIGH);
	DIO_WritePin(GLCD_CS2,HIGH);
	DIO_WritePin(GLCD_RST,HIGH);
	_delay_ms(40);
	GLCD_WriteIns(0x3E);				/* Display OFF */
	GLCD_WriteIns(0x40);				/* Set Y address (column=0) */
	GLCD_WriteIns(0xB8);				/* Set x address (page=0) */
	GLCD_WriteIns(0xC0);				/* Set z address (start line=0) */
	GLCD_WriteIns(0x3F);				/* Display ON */
}

static void GLCD_WriteIns(u8 Copy_u8Instruction)
{
	DIO_WritePin(GLCD_RS,LOW);
	DIO_WritePin(GLCD_RW,LOW);
	DIO_WritePort(GLCD_DATA_PORT,Copy_u8Instruction);
	DIO_WritePin(GLCD_EN,HIGH);
	_delay_us(5);
	DIO_WritePin(GLCD_EN,LOW);
	_delay_us(5);
}

static void GLCD_WriteData(u8 Copy_u8Data)
{
	DIO_WritePin(GLCD_RS,HIGH);
	DIO_WritePin(GLCD_RW,LOW);
	DIO_WritePort(GLCD_DATA_PORT,Copy_u8Data);
	DIO_WritePin(GLCD_EN,HIGH);
	_delay_us(5);
	DIO_WritePin(GLCD_EN,LOW);
	_delay_us(5);
}

void GLCD_voidWriteString(u8 Copy_u8PageNum,u8 Copy_u8Colums,u8*STR)
{
	u8 Local_u8Iterator=0,Local_u8Column;
	u8 Local_u8PageNumber=(0xB8+Copy_u8PageNum);
	u8 Local_u8Y_Address=Copy_u8Colums;
	
	DIO_WritePin(GLCD_CS1,LOW);
	DIO_WritePin(GLCD_CS2,HIGH);
	
	/*Set the starting page;*/
	GLCD_WriteIns(Local_u8PageNumber);
	GLCD_WriteIns(0x40 | Copy_u8Colums);
	for(Local_u8Iterator=0;STR[Local_u8Iterator];Local_u8Iterator++)
	{
		if(Local_u8Y_Address>=64)
		{
			Local_u8Y_Address=0;
			DIO_TogglePin(GLCD_CS1);
			DIO_TogglePin(GLCD_CS2);
			GLCD_WriteIns(Local_u8PageNumber);
		}
		if(STR[Local_u8Iterator]==' ')
		{
			for(Local_u8Column=0;Local_u8Column<FontWidth;Local_u8Column++)
			{
				GLCD_WriteData(0x00);
				Local_u8Y_Address++;
				if(Local_u8Y_Address>=64)
				{
					Local_u8Y_Address=0;
					DIO_TogglePin(GLCD_CS1);
					DIO_TogglePin(GLCD_CS2);
					GLCD_WriteIns(Local_u8PageNumber);
				}
			}
		}
		else
		{
			for(Local_u8Column=0;Local_u8Column<FontWidth;Local_u8Column++)
			{
				GLCD_WriteData(font[STR[Local_u8Iterator]-32][Local_u8Column]);
				Local_u8Y_Address++;
				if(Local_u8Y_Address>=64)
				{
					Local_u8Y_Address=0;
					DIO_TogglePin(GLCD_CS1);
					DIO_TogglePin(GLCD_CS2);
					GLCD_WriteIns(Local_u8PageNumber);
				}
			}
		}
	}
	// Reset Y address to start column after completion
	GLCD_WriteIns(0x40);						/* Set Y address (column=0) */
}


void GLCD_voidClear()
{
	u8 Local_u8Iterator1,Local_u8Iterator2;
	DIO_WritePin(GLCD_CS1,HIGH);
	DIO_WritePin(GLCD_CS2,HIGH);
	for(Local_u8Iterator1=0;Local_u8Iterator1<GLCD_TOTAL_PAGE;Local_u8Iterator1++)
	{
		GLCD_WriteIns(0xB8+Local_u8Iterator1);
		for(Local_u8Iterator2=0;Local_u8Iterator2<64;Local_u8Iterator2++)
		{
			GLCD_WriteData(0x00);
		}
	}
	GLCD_WriteIns(0xB8);     /* Set Y address (column=0) */
	GLCD_WriteIns(0x40);     /* Set x address (page=0) */
}

void GLCD_voidClearPage(u8 Copy_u8PageNum)
{
	u8 Local_u8Iterator;
	DIO_WritePin(GLCD_CS1,HIGH);
	DIO_WritePin(GLCD_CS2,HIGH);
	GLCD_WriteIns(0xB8+Copy_u8PageNum);
	for(Local_u8Iterator=0;Local_u8Iterator<64;Local_u8Iterator++)
	{
		GLCD_WriteData(0x00);
	}
	GLCD_WriteIns(0xB8);     /* Set x address (page=0) */
	GLCD_WriteIns(0x40);     /* Set Y address (column=0) */
}

void GLCD_voidWriteChar(u8 Copy_u8PageNum, u8 Copy_u8Column, u8 Local_u8Character)
 {
	u8 Local_u8Iterator;
	
	if(Copy_u8Column<64)
	{
		DIO_WritePin(GLCD_CS1,LOW);
		DIO_WritePin(GLCD_CS2,HIGH);
	}
	else
	{
		Copy_u8Column=Copy_u8Column-64;
		DIO_WritePin(GLCD_CS1,HIGH);
		DIO_WritePin(GLCD_CS2,LOW);
	}
	
	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 + Copy_u8Column);  // Set the column address
	
	for (Local_u8Iterator = 0; Local_u8Iterator < FontWidth; Local_u8Iterator++)
	{
		GLCD_WriteData(font[Local_u8Character - 32][Local_u8Iterator]);
	}
}


void GLCD_voidClearDot(u8 Copy_u8PageNum,u8 Copy_u8Column)
{
	u8 Local_u8Iterator;
	if(Copy_u8Column<64)
	{
		DIO_WritePin(GLCD_CS1,LOW);
		DIO_WritePin(GLCD_CS2,HIGH);
	}
	else
	{
		Copy_u8Column=Copy_u8Column-64;
		DIO_WritePin(GLCD_CS1,HIGH);
		DIO_WritePin(GLCD_CS2,LOW);
	}
	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 +Copy_u8Column);  // Set the column address
	GLCD_WriteData(0x00);
}

void GLCD_voidWriteDot(u8 Copy_u8PageNum,u8 Copy_u8Column)
{
	u8 Local_u8Iterator;
	if(Copy_u8Column<64)
	{
		DIO_WritePin(GLCD_CS1,LOW);
		DIO_WritePin(GLCD_CS2,HIGH);
	}
	else
	{
		Copy_u8Column=Copy_u8Column-64;
		DIO_WritePin(GLCD_CS1,HIGH);
		DIO_WritePin(GLCD_CS2,LOW);
	}
	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 +Copy_u8Column);  // Set the column address
	GLCD_WriteData(0xff);
}

void GLCD_voidClearChar(u8 Copy_u8PageNum,u8 Copy_u8Column)
{
	u8 Local_u8Iterator;
	if(Copy_u8Column<64)
	{
		DIO_WritePin(GLCD_CS1,LOW);
		DIO_WritePin(GLCD_CS2,HIGH);
	}
	else
	{
		Copy_u8Column=Copy_u8Column-64;
		DIO_WritePin(GLCD_CS1,HIGH);
		DIO_WritePin(GLCD_CS2,LOW);
	}
	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 +Copy_u8Column);  // Set the column address
	for(Local_u8Iterator=0;Local_u8Iterator<FontWidth;Local_u8Iterator++)
	{
		GLCD_WriteData(0x00);
	}
}


void GLCD_voidWriteNumber(u8 Copy_u8PageNum,u8 Copy_u8Column,u32 Copy_u32Num)
{
	u8 Local_u8Counter=0,Local_u8ReminderNum,c=0;
	u8 Num_Arr[10]={0};
	s8 Local_u8Iterator;
	GLCD_WriteIns(0xB8+Copy_u8PageNum);  // Set the page address
	GLCD_WriteIns(0x40 +Copy_u8Column);  // Set the column address
	while(Copy_u32Num)
	{
		Local_u8ReminderNum=Copy_u32Num%10;
		Num_Arr[Local_u8Counter]=Local_u8ReminderNum;
		Local_u8Counter++;
		Copy_u32Num/=10;
	}
	for(Local_u8Iterator=Local_u8Counter-1;Local_u8Iterator>=0;Local_u8Iterator--)
	{
		GLCD_voidWriteChar(Copy_u8PageNum,(Copy_u8Column+((Local_u8Counter-Local_u8Iterator-1)*5)),48+Num_Arr[Local_u8Iterator]);
		c++;
	}
}

void GLCD_voidDrawBox(u8 Copy_u8StartWidth,u8 Copy_u8EndWidth,u8 Copy_u8StartPage,u8 Copy_u8EndPage)
{
	u8 Local_u8Offest;
	u8 Local_u8Iterator1,Local_u8Iterator2;
	u8 Local_u8Y_Address=Copy_u8StartWidth;
	DIO_WritePin(GLCD_CS1,LOW);
	DIO_WritePin(GLCD_CS2,HIGH);
	for (Local_u8Iterator1 = Copy_u8StartPage; Local_u8Iterator1 <= Copy_u8EndPage; Local_u8Iterator1++)
	{
		Local_u8Y_Address=Copy_u8StartWidth;
		if(Local_u8Y_Address>=64)
		{
			Local_u8Y_Address=Local_u8Y_Address-64;
			DIO_TogglePin(GLCD_CS1);
			DIO_TogglePin(GLCD_CS2);
		}
		GLCD_WriteIns(0xB8 + Local_u8Iterator1); // Set the page address
		GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
		GLCD_WriteIns(0xC0);
		for (Local_u8Iterator2 = Copy_u8StartWidth; Local_u8Iterator2 <= Copy_u8EndWidth; Local_u8Iterator2++)
		{
			if(Local_u8Y_Address>=64)
			{
				Local_u8Y_Address=Local_u8Y_Address-64;
				DIO_TogglePin(GLCD_CS1);
				DIO_TogglePin(GLCD_CS2);
				GLCD_WriteIns(0xB8 + Local_u8Iterator1);
				GLCD_WriteIns(0x40 + Local_u8Y_Address);
				GLCD_WriteIns(0xC0);
			}
			GLCD_WriteData(0xff);
			Local_u8Y_Address++;
		}
		DIO_WritePin(GLCD_CS1,LOW);
		DIO_WritePin(GLCD_CS2,HIGH);
	}
}

void GLCD_voidClearBox(u8 Copy_u8StartWidth,u8 Copy_u8EndWidth,u8 Copy_u8StartPage,u8 Copy_u8EndPage)
{
	u8 Local_u8Iterator1,Local_u8Iterator2;
	u8 Local_u8Y_Address=Copy_u8StartWidth;
	
	DIO_WritePin(GLCD_CS1,LOW);
	DIO_WritePin(GLCD_CS2,HIGH);
	for (Local_u8Iterator1 = Copy_u8StartPage; Local_u8Iterator1 <= Copy_u8EndPage; Local_u8Iterator1++)
	{
		Local_u8Y_Address=Copy_u8StartWidth;
		if(Local_u8Y_Address>=64)
		{
			Local_u8Y_Address=Local_u8Y_Address-64;
			DIO_TogglePin(PINB0);
			DIO_TogglePin(PINB1);
		}
		GLCD_WriteIns(0xB8 + Local_u8Iterator1); // Set the page address
		GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
		GLCD_WriteIns(0xC0);
		
		for (Local_u8Iterator2 = Copy_u8StartWidth; Local_u8Iterator2 <= Copy_u8EndWidth; Local_u8Iterator2++)
		{
			if(Local_u8Y_Address>=64)
			{
				Local_u8Y_Address=Local_u8Y_Address-64;
				DIO_TogglePin(GLCD_CS1);
				DIO_TogglePin(GLCD_CS2);
				GLCD_WriteIns(0xB8 + Local_u8Iterator1);
				GLCD_WriteIns(0x40 + Local_u8Y_Address);
				GLCD_WriteIns(0xC0);
			}
			GLCD_WriteData(0x00);
			Local_u8Y_Address++;
		}
		DIO_WritePin(GLCD_CS1,LOW);
		DIO_WritePin(GLCD_CS2,HIGH);
	}
}
void GLCD_voidPrintBird(u8 Copy_u8PageNum, u8 Copy_u8Column)
{
	u8 Local_u8Iterator;
	u8 Local_u8Y_Address=Copy_u8Column;
	u8 arr[10]={0x18, 0x3C, 0x7E, 0xFF, 0xFF,0xEF, 0x6A, 0x2E, 0x38, 0x08};
	
	DIO_WritePin(GLCD_CS1,LOW);
	DIO_WritePin(GLCD_CS2,HIGH);

	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
	
	for (Local_u8Iterator = 0; Local_u8Iterator < 10; Local_u8Iterator++)
	{
		if(Local_u8Y_Address>=64)
		{
			Local_u8Y_Address=Local_u8Y_Address-64;
			DIO_TogglePin(GLCD_CS1);
			DIO_TogglePin(GLCD_CS2);
			GLCD_WriteIns(0xB8 + Copy_u8PageNum);
			GLCD_WriteIns(0x40 + Local_u8Y_Address);
			GLCD_WriteIns(0xC0);
		}
		GLCD_WriteData(arr[Local_u8Iterator]);
		Local_u8Y_Address++;
	}
}

void GLCD_voidClearBird(u8 Copy_u8PageNum, u8 Copy_u8Column)
{
	u8 Local_u8Iterator;
	u8 Local_u8Y_Address=Copy_u8Column;
	
	DIO_WritePin(GLCD_CS1,LOW);
	DIO_WritePin(GLCD_CS2,HIGH);

	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
	
	for (Local_u8Iterator = 0; Local_u8Iterator < 11; Local_u8Iterator++)
	{
		if(Local_u8Y_Address>=64)
		{
			Local_u8Y_Address=Local_u8Y_Address-64;
			DIO_TogglePin(GLCD_CS1);
			DIO_TogglePin(GLCD_CS2);
			GLCD_WriteIns(0xB8 + Copy_u8PageNum);
			GLCD_WriteIns(0x40 + Local_u8Y_Address);
			GLCD_WriteIns(0xC0);
		}
		GLCD_WriteData(0x00);
		Local_u8Y_Address++;
	}
}


void GLCD_voidDrawSadFace(u8 Copy_u8Column,u8 Copy_u8PageNum) {
	u8 Local_u8Iterator;
	u8 Local_u8Y_Address=Copy_u8Column;
	u8 Local_u8Flag=0;
	uint8_t sad_face[] = {
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x3F, 0x3F,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0x3F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFC, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00,
		0x00, 0x00, 0x00, 0xF0, 0xF8, 0xFC, 0x1C, 0x1C, 0x1C,0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C,0x1C, 0x1C, 0x1C, 0x1C,0x1C, 0x1C, 0x1C, 0x1C, 0xF8, 0xF8, 0xF0, 0x00, 0x00,0x00
	};
	
	DIO_WritePin(GLCD_CS1,LOW);
	DIO_WritePin(GLCD_CS2,HIGH);

	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
	
	 for (u8 page = 0; page < 4; page++)
	 {
		 Local_u8Flag=0;
		 Local_u8Y_Address=Copy_u8Column;
		 GLCD_WriteIns(0xB8 + Copy_u8PageNum+page); // Set the page address
		 GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
		 
		 for (Local_u8Iterator = 0; Local_u8Iterator < 30; Local_u8Iterator++)
		 {
			 if(Local_u8Y_Address>=64)
			 {
				 Local_u8Flag=1;
				 Local_u8Y_Address=Local_u8Y_Address-64;
				 DIO_TogglePin(GLCD_CS1);
				 DIO_TogglePin(GLCD_CS2);
				 GLCD_WriteIns(0xB8 + Copy_u8PageNum+page);
				 GLCD_WriteIns(0x40 + Local_u8Y_Address);
				 GLCD_WriteIns(0xC0);
			 }
			 GLCD_WriteData(sad_face[page * 30 + Local_u8Iterator]);
			 Local_u8Y_Address++;
		 }
		 if(Local_u8Flag==1)
		 {
			 DIO_TogglePin(GLCD_CS1);
			 DIO_TogglePin(GLCD_CS2);
		 }
	 }
}


void GLCD_voidCryMoving(u8 Copy_u8Column,u8 Copy_u8PageNum)
{
	static u8 Local_u8CryNum=0x0F;
	u8 Local_u8Iterator;
	GLCD_voidWriteChar(Copy_u8PageNum,Copy_u8Column+5,' ');
	GLCD_voidWriteChar(Copy_u8PageNum,Copy_u8Column+22,' ');
    if(Local_u8CryNum==0)
    {
    	Local_u8CryNum=0x0F;	
    }
    DIO_WritePin(GLCD_CS1,LOW);
    DIO_WritePin(GLCD_CS2,HIGH);
    
    GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
    GLCD_WriteIns(0x40 +Copy_u8Column);  // Set the column address
	
	GLCD_WriteIns(0x40 +Copy_u8Column+5);  // Set the column address
	GLCD_WriteData(Local_u8CryNum);
	GLCD_WriteData(Local_u8CryNum);
	GLCD_WriteData(Local_u8CryNum);
	
	GLCD_WriteIns(0x40 +Copy_u8Column+22);
	GLCD_WriteData(Local_u8CryNum);
	GLCD_WriteData(Local_u8CryNum);
	GLCD_WriteData(Local_u8CryNum);

    Local_u8CryNum=Local_u8CryNum<<1;

}

void GLCD_voidBigBird(u8 Copy_u8Column,u8 Copy_u8PageNum)
{
	u8 Local_u8Iterator;
	u8 Local_u8Y_Address=Copy_u8Column;
	u8 Local_u8Flag=0;
	u8 arr[]={0xC0, 0xC0, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xC8, 0xC8, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x80,
		       0x03, 0x03, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x01
			 };
	DIO_WritePin(GLCD_CS1,LOW);
	DIO_WritePin(GLCD_CS2,HIGH);

	GLCD_WriteIns(0xB8 + Copy_u8PageNum); // Set the page address
	GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
	
	for (u8 page = 0; page < 2; page++)
	{
		Local_u8Flag=0;
		Local_u8Y_Address=Copy_u8Column;
		GLCD_WriteIns(0xB8 + Copy_u8PageNum+page); // Set the page address
		GLCD_WriteIns(0x40 +Local_u8Y_Address);  // Set the column address
		
		for (Local_u8Iterator = 0; Local_u8Iterator < 25; Local_u8Iterator++)
		{
			if(Local_u8Y_Address>=64)
			{
				Local_u8Flag=1;
				Local_u8Y_Address=Local_u8Y_Address-64;
				DIO_TogglePin(GLCD_CS1);
				DIO_TogglePin(GLCD_CS2);
				GLCD_WriteIns(0xB8 + Copy_u8PageNum+page);
				GLCD_WriteIns(0x40 + Local_u8Y_Address);
				GLCD_WriteIns(0xC0);
			}
			GLCD_WriteData(arr[page * 25 + Local_u8Iterator]);
			Local_u8Y_Address++;
		}
		if(Local_u8Flag==1)
		{
			DIO_TogglePin(GLCD_CS1);
			DIO_TogglePin(GLCD_CS2);
		}
	}
}


void GLCD_voidBigBirdMoving(u8 Copy_u8Column,u8 Copy_u8PageNum)
{
	u8 Local_u8Iterator=0;
	GLCD_voidBigBird(Copy_u8Column+Local_u8Iterator,Copy_u8PageNum);
	for(Local_u8Iterator=1;Local_u8Iterator<10;Local_u8Iterator++)
	{
		GLCD_voidClearDot(Copy_u8PageNum,Copy_u8Column+Local_u8Iterator-1);
		GLCD_voidClearDot(Copy_u8PageNum+1,Copy_u8Column+Local_u8Iterator-1);
		GLCD_voidBigBird(Copy_u8Column+Local_u8Iterator,Copy_u8PageNum);
		_delay_ms(5);
	}
}


void GLCD_voidetPixel(u8 copy_u8X,u8 Copy_u8Y)
{
	u8 Local_u8Iterator;
	
	if(copy_u8X<64)
	{
		DIO_WritePin(GLCD_CS1,LOW);
		DIO_WritePin(GLCD_CS2,HIGH);
	}
	else
	{
		copy_u8X=copy_u8X-64;
		DIO_WritePin(GLCD_CS1,HIGH);
		DIO_WritePin(GLCD_CS2,LOW);
	}
	
	GLCD_WriteIns(0xB8 + Copy_u8Y); // Set the page address
	GLCD_WriteIns(0x40 + copy_u8X);  // Set the column address
	
}