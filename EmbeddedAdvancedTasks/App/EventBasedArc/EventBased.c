/*
 * EventBased.c
 *
 * Created: 10/30/2024 2:53:28 AM
 *  Author: Demiana Younes
 */ 

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

#include "DIO_Interface.h"
#include "Ex_Interrupt_Interface.h"
#include "Timer_Interface.h"

#include "Queue_Interface.h"

#include "EventBased_Interface.h"
#include "EventBased_Private.h"
#include "EventBased_Config.h"

CircularQueue_type Queue;

/**
 * @brief Initializes the event-driven architecture components, configuring the 
 *        digital I/O, external interrupts, timers, and the event queue.
 *
 *        Sets up DIO, defines the trigger for external interrupts, and initializes
 *        Timer1 for generating periodic timer events. Registers callback functions
 *        for handling external and timer-based interrupts and enables global 
 *        interrupts.
 *
 * @return None
 */
void EventBased_Init()
{
	DIO_Init();
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_SetCallBack(EX_INT0,CallBack_INT0);
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_64);
	Timer1_OCRA1Mode(OCRB_NON_INVERTING);
	OCR1A=SET_50MS;
	Timer1_OCA_SetCallBack(CallBack_Timer1);
	CircularQueue_Init(&Queue);
	sei();  // Enable global interrupts
	EXI_Enable(EX_INT0);
	Timer1_OCA_InterruptEnable();
}
/**
 * @brief Callback function triggered by the external interrupt (INT0).
 *
 *        Enqueues an event in the circular queue indicating that BUTTON1 
 *        was pressed, triggered by an external interrupt.
 *
 * @return None
 */
static void CallBack_INT0()
{
	Enqueue(&Queue,BUTTON1_WITH_EXT_INT0);
}

/**
 * @brief Callback function for Timer1 compare match events.
 *
 *        Checks the state of a button connected to PINC7. If the button 
 *        is pressed (PINC7 is LOW) and a flag is cleared, an event for 
 *        BUTTON2 is enqueued. The flag prevents duplicate entries until 
 *        the button is released.
 *
 * @return None
 */
static void CallBack_Timer1()
{
	static u8 Local_u8Flag=0;
	if(DIO_ReadPin(PINC7)==LOW && Local_u8Flag==0)
	{
		Enqueue(&Queue,BUTTON2_WITH_TIMER_INT);
		Local_u8Flag=1;
	}
	else if(DIO_ReadPin(PINC7)==HIGH)
	{
		Local_u8Flag=0;
	}
}

/**
 * @brief Processes queued button events by reading from the circular queue.
 *        Dequeues an event and performs actions like toggling specific pins
 *        based on the event type. If the queue is empty, it sets a default pin.
 *
 * @return None
 */
void EventBased_Runnable()
{
	u8 Local_u8Data=0;
	DeQueue(&Queue,&Local_u8Data);
	switch(Local_u8Data)
	{
		case BUTTON1_WITH_EXT_INT0:
		DIO_TogglePin(PINC1);
		break;
		case BUTTON2_WITH_TIMER_INT:
		DIO_TogglePin(PINC2);
		break;
		default:
		DIO_WritePin(PINC0,HIGH);
	}
	
}