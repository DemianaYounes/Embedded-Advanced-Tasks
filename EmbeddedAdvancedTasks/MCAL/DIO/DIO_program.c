
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"



void DIO_Init(void)
{
	DIO_Pin_type i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinsStatusArray[i]);
	}
	
}

static void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	DIO_Port_type port =pin/8;
	u8 pin_num=pin%8;
	
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT( DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT( DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT( DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT( DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}
}

/*void DIO_InitPin2(DIO_Port_type port,u8 pin_num,DIO_PinStatus_type status)
{
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}
}*/
/*void DIO_InitPin3(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	switch(status)
	{
		case OUTPUT:
		if(pin<=PINA7)
		{
			SET_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
		}
		else if(pin>=PINB0 && pin<=PINB7)
		{
			SET_BIT(DDRB,pin-PINA7-1);
			CLR_BIT(PORTB,pin-PINA7-1);
		}
		else if(pin>=PINC0 && pin<=PINC7)
		{
			SET_BIT(DDRC,pin-PINB7-1);
			CLR_BIT(PORTC,pin-PINB7-1);
		}
		else if(pin>=PIND0 && pin<=PIND7)
		{
			SET_BIT(DDRD,pin-PINC7-1);
			CLR_BIT(PORTD,pin-PINC7-1);
		}
		break;
		case INFREE:
		if(pin<=PINA7)
		{
			CLR_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
		}
		else if(pin>=PINB0 && pin<=PINB7)
		{
			CLR_BIT(DDRB,pin-PINA7-1);
			CLR_BIT(PORTB,pin-PINA7-1);
		}
		else if(pin>=PINC0 && pin<=PINC7)
		{
			CLR_BIT(DDRC,pin-PINB7-1);
			CLR_BIT(PORTC,pin-PINB7-1);
		}
		else if(pin>=PIND0 && pin<=PIND7)
		{
			CLR_BIT(DDRD,pin-PINC7-1);
			CLR_BIT(PORTD,pin-PINC7-1);
		}
		break;
		case INPULL:
		if(pin<=PINA7)
		{
			CLR_BIT(DDRA,pin);
			SET_BIT(PORTA,pin);
		}
		else if(pin>=PINB0 && pin<=PINB7)
		{
			CLR_BIT(DDRB,pin-PINA7-1);
			SET_BIT(PORTB,pin-PINA7-1);
		}
		else if(pin>=PINC0 && pin<=PINC7)
		{
			CLR_BIT(DDRC,pin-PINB7-1);
			SET_BIT(PORTC,pin-PINB7-1);
		}
		else if(pin>=PIND0 && pin<=PIND7)
		{
			CLR_BIT(DDRD,pin-PINC7-1);
			SET_BIT(PORTD,pin-PINC7-1);
		}
		break;
	}
	
}*/

/*void DIO_WritePin2(DIO_Port_type port,u8 pin_num,DIO_PinVoltage_type volt)
{
	if(volt==HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(PORTC,pin_num);
			break;
		}
	}
	else if(volt==LOW)
	{
		switch(port)
		{
			case PA:
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(PORTC,pin_num);
			break;
		}
	}
	else
	{
		// dO nothing 
	}
}*/

void DIO_WritePin(DIO_Pin_type pin,DIO_PinVoltage_type volt)
{
	DIO_Port_type port =pin/8;
	u8 pin_num=pin%8;
	
	
	if (volt==HIGH)
	{
		switch(port)
		{
			case PA:
			
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			
			SET_BIT(PORTD,pin_num);
			break;
		}
		
	}
	else if (volt==LOW)
	{
		switch(port)
		{
			case PA:
			
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			
			CLR_BIT(PORTD,pin_num);
			break;
		}
	}
	else
	{
		/* do nothing */
	}
	
}
/*DIO_PinVoltage_type DIO_ReadPin2(DIO_Port_type port,u8 pin_num)
{
	DIO_PinVoltage_type volt=LOW;
	switch(port)
	{
		case PA:
		volt=READ_BIT(PINA,pin_num);
		break;
		case PB:
		volt=READ_BIT(PINA,pin_num);
		break;
		case PC:
		volt=READ_BIT(PINA,pin_num);
		break;
		case PD:
		volt=READ_BIT(PINA,pin_num);
		break;
	}
	return volt;
}*/
/*DIO_PinVoltage_type DIO_ReadPin3(DIO_Pin_type pin)
{
	DIO_PinVoltage_type volt=LOW;
	if(pin<=PINA7)
	{
		volt=READ_BIT(PINA,pin);
	}
	else if(pin>=PINB0 && pin<=PINB7)
	{
		volt=READ_BIT(PINB,pin-PINA7-1);
	}
	else if(pin>=PINC0 && pin<=PINC7)
	{
		volt=READ_BIT(PINC,pin-PINB7-1);
	}
	else if(pin>=PIND0 && pin<=PIND7)
	{
		volt=READ_BIT(PIND,pin-PINC7-1);
	}
	return volt;
}*/
/*Error_t DIO_ReadPin(DIO_Port_type port,u8 pin_num,DIO_PinVoltage_type*pvolt)
{
	if(pvolt==NULL_PTR)
	{
		return NULL_PTR_ERROR:
	}
	else if(port>PD || pin_num>7)
	{
		return OUT_OF_RANGE;
	}
	else
	{
		switch(port)
		{
			case PA:
			*pvolt=READ_BIT(PINA,pin_num);
			break;
			case PB:
			*pvolt=READ_BIT(PINA,pin_num);
			break;
			case PC:
			*pvolt=READ_BIT(PINA,pin_num);
			break;
			case PD:
			*pvolt=READ_BIT(PINA,pin_num);
			break;
		}
		return OK;
	}
}*/

DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_Port_type port =pin/8;
	u8 pin_num=pin%8;
	DIO_PinVoltage_type volt=LOW;
	
	switch(port)
	{
		case PA:
		
		volt=READ_BIT(PINA,pin_num);
		break;
		case PB:
		
		volt=READ_BIT(PINB,pin_num);
		break;
		case PC:
		
		volt=READ_BIT(PINC,pin_num);
		break;
		case PD:
		
		volt=READ_BIT(PIND,pin_num);
		break;
	}
	
	return volt;
}
void DIO_TogglePin(DIO_Pin_type pin)
{
	if(pin<=PINA7)
	{
		TOGGLE_BIT(PORTA,pin);
	}
	else if(pin>=PINB0 && pin<=PINB7)
	{
		TOGGLE_BIT(PORTB,(pin-PINA7-1));
	}
	else if(pin>=PINC0 && pin<=PINC7)
	{
		TOGGLE_BIT(PORTC,(pin-PINB7-1));
	}
	else if(pin>=PIND0 && pin<=PIND7)
	{
		TOGGLE_BIT(PORTD,(pin-PINC7-1));
	}
}

void DIO_WritePort(DIO_Port_type port,u8 value)
{
	switch(port)
	{
		case PA:
		PORTA=value;
		break;
		case PB:
		PORTB=value;
		break;
		case PC:
		PORTC=value;
		break;
		case PD:
		PORTD=value;
		break;
	}
}
u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 value=0;
	switch(port)
	{
		case PA:
		value=PINA;
		break;
		case PB:
		value=PINB;
		break;
		case PC:
		value=PINC;
		break;
		case PD:
		value=PIND;
		break;
	}
	return value;
}