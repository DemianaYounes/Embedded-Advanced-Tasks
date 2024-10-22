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


static void (*Stcak_Arr[STACK_SIZE])(void);
static void (*currentState)(void) = NULL;
static s8 StackPointer=STACK_POINTER_INIT;

static void Stack_CallBack()
{
	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	if(Local_u8Counter==NUMBER_OF_SECOND)
	{
		Stack_Pop();
		if (StackPointer == -1)
	    {
			// If the stack is empty, reset and start with red
			Stack_Push(Red_Led);
		}
		else
		{
			// Cycle through states
			if (currentState == Red_Led) {
				Stack_Push(Yellow_Led);
				} else if (currentState == Green_Led) {
				Stack_Push(Red_Led);
				} else if (currentState == Yellow_Led) {
				Stack_Push(Green_Led);
			}
		}
		Local_u8Counter=0;
	}
	
}
void TrafficLight_voidInit(void)
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
	
	/* Initialize the stack with state functions*/
	Stack_Push(Green_Led);
	Stack_Push(Yellow_Led);
	Stack_Push(Red_Led);
	Stack_Pop(); // Pop the first state to set currentState
}

void TrafficLight_voidRunnable(void)
{
	if(currentState!=NULL)
	{
		currentState();
	}
	else
	{
		/*Do Nothing*/
	}

}

static Stack_Status_t Stack_Push(void(*LocalFptr)(void))
{
	Stack_Status_t Local_StackStatus=STACK_EMPTY;
	if(StackPointer<STACK_SIZE-1)
	{
		Stcak_Arr[++StackPointer]=LocalFptr;
		Local_StackStatus=STACK_DONE;
	}
	else
	{
		Local_StackStatus=STACK_FULL;
	}
	return Local_StackStatus;
}

static Stack_Status_t Stack_Pop(void)
{
	Stack_Status_t Local_StackStatus=STACK_EMPTY;
	if(StackPointer>-1)
	{
		currentState=Stcak_Arr[StackPointer--];
		Local_StackStatus=STACK_DONE;
	}
	else
	{
		Local_StackStatus=STACK_EMPTY;
	}
	return Local_StackStatus;
}

static void Red_Led(void)
{
	DIO_WritePin(LED_YELLOW_PIN,LOW);
	DIO_WritePin(LED_GREEN_PIN,LOW);
	DIO_WritePin(LED_RED_PIN,HIGH);
	LCD_SetCurser(0,12);
	LCD_WriteString("      ");
	LCD_SetCurser(0,0);
	LCD_WriteString("Stop Driving");
}

static void Yellow_Led(void)
{
	DIO_WritePin(LED_GREEN_PIN,LOW);
	DIO_WritePin(LED_RED_PIN,LOW);
	DIO_WritePin(LED_YELLOW_PIN,HIGH);
	LCD_SetCurser(0,0);
	LCD_WriteString("Stopping Soon");
}

static void Green_Led(void)
{
	DIO_WritePin(LED_RED_PIN,LOW);
	DIO_WritePin(LED_YELLOW_PIN,LOW);
	DIO_WritePin(LED_GREEN_PIN,HIGH);
	LCD_SetCurser(0,13);
	LCD_WriteString("      ");
	LCD_SetCurser(0,0);
	LCD_WriteString("Start Driving");
}
