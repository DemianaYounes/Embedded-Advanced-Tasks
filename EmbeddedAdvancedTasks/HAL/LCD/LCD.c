#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"

#include "LCD_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Private.h"

#define F_CPU  8000000
#include <util/delay.h>

#if LCD_MODE==_8_BIT
void LCD_Init(void)
{
	/* 8-Bit Initialization */
	_delay_ms(50);
	/*Function Set
	*DL:set data length (0) 4-bit mode and (1) 8-bit mode
	*N:set number of lines (0) 1 line and (1) 2 line
	*F:set character font (0) 5*7 dots and (1) 5*10 dots
	*-: do not care ,I will put zero
	* i will set 0x00111000 (0x38) 8 bit mode, 2 line and 5*7 dots*/
	LCD_WriteIns(0x38);
	/*Display on/off control
	*D:entry display (0) off and (1) on
	*C:the curser display (0) doesn't display and (1) display
	*B:the curser blink (0) the blink is off (1) the blink is on
	*i will set 0x00001100 (0x0c) display  on,  curser display off and curser blink off */
	LCD_WriteIns(0x0c); //0x0e  ,  0x0f
	/*Display Clear*/
	LCD_WriteIns(0x01); //clear screen
	_delay_ms(1);
	/*Entry mode set
	*I/D: (1) increase and (0) decrease 
	*S:shift (1) shift to left and (0) shift to write 
	* i will set 0x00000110 (0x06) I/D increase and shift to right */
	LCD_WriteIns(0x06);
}
static void LCD_WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins); 
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data); 
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
#elif LCD_MODE==_4_BIT
void LCD_Init(void)
{
	/* 8-Bit Initialization */
	_delay_ms(50);
	/*send the high part*/
	LCD_WriteIns(0x02);
	/*Function Set
	*DL:set data length (0) 4-bit mode and (1) 8-bit mode
	*N:set number of lines (0) 1 line and (1) 2 line
	*F:set character font (0) 5*7 dots and (1) 5*10 dots
	*-: do not care ,I will put zero
	* i will set 0x00101000 (0x28) 4 bit mode, 2 line and 5*7 dots*/
	LCD_WriteIns(0x28);
	/*Display on/off control
	*D:entry display (0) off and (1) on
	*C:the curser display (0) doesn't display and (1) display
	*B:the curser blink (0) the blink is off (1) the blink is on
	*i will set 0x00001100 (0x0c) display  on,  curser display off and curser blink off */
	LCD_WriteIns(0x0c); //0x0e  ,  0x0f
	/*Display Clear*/
	LCD_WriteIns(0x01); //clear screen
	_delay_ms(1);
	/*Entry mode set
	*I/D: (1) increase and (0) decrease 
	*S:shift (1) shift to left and (0) shift to write 
	* i will set 0x00000110 (0x06) I/D increase and shift to right */
	LCD_WriteIns(0x06);
}
static void LCD_WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
#endif



void LCD_WriteChar(u8 ch)
{
	LCD_WriteData(ch);
}
void LCD_WriteString(u8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		LCD_WriteData(str[i]);
	}
}

void LCD_SetCurser(u8 line ,u8 cell)
{
	/********** Line 0:1 Cell 0:15 **********
	*bits from 0:7
	*to write data in specific address you must set 1 in the bit 7 to become :0x80
	*so 1 bit to set DDRAM address and 7 bit to write data 
	*the second line start address with 0x40 , so to write the second line must set 1 to bit 6:0x40
	* to write data and start from the next line must set :0x80+0x40+cell number = 0xc0+cell number
	*to write data and start from the first line must set :0x80+cell number
	*/
	if(line==0)
	{
		LCD_WriteIns(0x80+cell);
	}
	else if(line==1)
	{
		//LCD_WriteIns(0xc0+cell);
		LCD_WriteIns(0x80+0x40+cell);
	}
	else
	{
		/*do nothing*/
	}
}
void LCD_WriteNumber(s32 num)
{
	u8 arr[20],i=0;
	s8 j;
	if(num<0)
	{
		LCD_WriteChar('-');
		num=num*(-1);
	}
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	while(num)
	{
		arr[i]=num%10+'0';
		num=num/10;
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(arr[j]);
	}
}
void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		//LCD_WriteChar(((num>>i)&1)+'0');
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}
void LCD_WriteHexa_Method2(u8 num)
{
	u8 HL,LL,arr[6]={'a','b','c','d','e','f'};
	LL=num&0x0f;
	HL=(num>>4)&0x0f;
	LCD_WriteData('0');
	LCD_WriteData('x');
	if(HL>9)
	{
		LCD_WriteChar(arr[HL-10]);
	}
	else
	{
		LCD_WriteChar(HL+'0');
	}
	if(LL>9)
	{
		LCD_WriteChar(arr[LL-10]);
	}
	else
	{
		LCD_WriteChar(LL+'0');
	}
}

void LCD_WriteHexa(u8 num)
{
	u8 HL,LL;
	LL=num&0x0f;
	HL=(num>>4)&0x0f;
	LCD_WriteData('0');
	LCD_WriteData('x');
	if(HL>9)
	{
		LCD_WriteChar(HL-10+'A');
	}
	else
	{
		LCD_WriteChar(HL+'0');
	}
	if(LL>9)
	{
		LCD_WriteChar(LL-10+'A');
	}
	else
	{
		LCD_WriteChar(LL+'0');
	}
}

void LCD_Clear(void)
{
	LCD_WriteIns(0x01);
}

void LCD_WriteNumber_4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}

void LCD_CustomChar(u8 loc,u8*pattern)
{
	LCD_WriteIns(0x40+loc*8);
	for(u8 i=0;i<8;i++)
	{
		LCD_WriteChar(pattern[i]);
	}
	LCD_WriteIns(0x80);
}