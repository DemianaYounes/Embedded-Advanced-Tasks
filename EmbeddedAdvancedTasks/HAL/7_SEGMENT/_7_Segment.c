
#include "StdTypes.h"
/*Include From MCAL*/
#include "DIO_Interface.h"
/*Include From HAL*/
#include "_7_Segment_Interface.h"
#include "_7_Segment_Private.h"
#include "_7_Segment_Cfg.h"

#define F_CPU  8000000
#include <util/delay.h>


void Seven_SegmentDisplay(u8 num)
{
	u8 p1,p2;
	p1=num/10;
	p2=num%10;
	/*for Common Anode*/
	//SEGMENT_PORT=~SegmentArr[p1];
	/* for Common Cathode */
	DIO_WritePin(SEGMENT_PIN1,HIGH);
	DIO_WritePort(SEGMENT_PORT,SegmentArr[p2]<<1);
	DIO_WritePin(SEGMENT_PIN2,LOW);
	_delay_ms(1);
	DIO_WritePin(SEGMENT_PIN2,HIGH);
	DIO_WritePort(SEGMENT_PORT,SegmentArr[p1]<<1);
	DIO_WritePin(SEGMENT_PIN1,LOW);
	_delay_ms(1);
}
void Seven_SegmentDisplay_BCD(u8 num)
{
	unsigned char p1,p2,Value_Port;
	p1=num/10;
	p2=num%10;
	Value_Port=(p1<<4)|(p2);
	DIO_WritePort(SEGMENT_PORT,Value_Port);
}
void Seven_SegmentDisplay_BCD_HEXA(u8 num)
{
	DIO_WritePort(SEGMENT_PORT,num);
}