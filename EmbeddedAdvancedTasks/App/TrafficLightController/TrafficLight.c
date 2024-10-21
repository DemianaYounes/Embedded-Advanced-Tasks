/*
 * TrafficLight.c
 *
 * Created: 10/21/2024 4:52:01 PM
 *  Author: Demiana Younes
 */ 

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

#include "DIO_Interface.h"
#include "Timer_Interface.h"

#include "LCD_Interface.h"

#include "TrafficLight_Interface.h"
#include "TraficLight_Private.h"
#include "TrafficLight_Cfg.h"



static u8 Stcak_Arr[STACK_SIZE];
static s8 StackPointer=STACK_POINTER_INIT;
static volatile u8 Data=5;
static volatile u8 Counter=0;

static void Stack_CallBack()
{
	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	Counter=Local_u8Counter;
	if(Local_u8Counter==SECOND_NUMBERS)
	{
		DIO_WritePin(Data+LED_RED_PIN,LOW);
		Stack_Pop(&Data);
		DIO_WritePin(Data+LED_RED_PIN,HIGH);
		Local_u8Counter=0;
	}
	
}
void TracfficLight_voidInit(void)
{
	DIO_Init();
	LCD_Init();
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_64);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	/*Value of 1 sec*/
	OCR1A=ONE_SECOND_WITH_64PRESCALLER_VALUE; 
	Timer1_OCA_SetCallBack(Stack_CallBack);
	sei();
	Timer1_OCA_InterruptEnable();
}

void TracfficLight_voidRunnable(void)
{
	Stack_Status_t Local_StackStatus=STACK_EMPTY;
	if(StackPointer==STACK_POINTER_INIT)
	{
		Local_StackStatus=Stack_Push(GRREN);
		if(Local_StackStatus==STACK_DONE)
		{
			Local_StackStatus=Stack_Push(YELLOW);
			if(Local_StackStatus==STACK_DONE)
			{
				Local_StackStatus=Stack_Push(RED);
			}
		}
	}
	else
	{
		LCD_SetCurser(1,0);
		LCD_WriteString("Sec:");
		while(StackPointer!=STACK_POINTER_INIT)
		{
			switch(Data)
			{
				case RED:
				LCD_SetCurser(0,12);
				LCD_WriteString("      ");
				LCD_SetCurser(0,0);
				LCD_WriteString("Stop Driving");
				break;
				case YELLOW:
				LCD_SetCurser(0,0);
				LCD_WriteString("Stopping Soon");
				break;
				case GRREN:
				LCD_SetCurser(0,13);
				LCD_WriteString("      ");
				LCD_SetCurser(0,0);
				LCD_WriteString("Start Driving");
				break;
				default:
				LCD_SetCurser(0,0);
				LCD_WriteString(" Traffic Light ");
			}
			LCD_SetCurser(1,5);
			LCD_WriteNumber(Counter);
		}
	}

	
}

static Stack_Status_t Stack_Push(u8 Copy_u8Data)
{
	Stack_Status_t Local_StackStatus=STACK_EMPTY;
	if(StackPointer<STACK_SIZE-1)
	{
		Stcak_Arr[++StackPointer]=Copy_u8Data;
		Local_StackStatus=STACK_DONE;
	}
	else
	{
		Local_StackStatus=STACK_FULL;
	}
	return Local_StackStatus;
}

static Stack_Status_t Stack_Pop(u8* Copy_pu8Data)
{
	Stack_Status_t Local_StackStatus=STACK_EMPTY;
	if(StackPointer>-1)
	{
		*Copy_pu8Data=Stcak_Arr[StackPointer--];
		Local_StackStatus=STACK_DONE;
	}
	else
	{
		Local_StackStatus=STACK_EMPTY;
	}
	return Local_StackStatus;
}
static u8 Stack_u8GetCurrentState(void)
{
	if(StackPointer>-1)
	{
		return Stcak_Arr[StackPointer];
	}
	return STACK_POINTER_INIT;
}