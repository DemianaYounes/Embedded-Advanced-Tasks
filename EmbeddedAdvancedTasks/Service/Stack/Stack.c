/*
 * Stack.c
 *
 * Created: 11/14/2024 4:25:14 AM
 *  Author: Demiana Younes
 */ 

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

#include "Stack_Interface.h"
#include "Stack_Config.h"
#include "Stack_Private.h"

static void (*Stcak_Arr[STACK_SIZE])(void);
void (*currentState)(void) = NULL;
static s8 StackPointer=STACK_POINTER_INIT;

Stack_Status_t Stack_Push(void(*LocalFptr)(void))
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

Stack_Status_t Stack_Pop(void)
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