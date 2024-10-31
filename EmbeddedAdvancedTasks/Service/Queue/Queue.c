/*
 * Queue.c
 *
 * Created: 10/30/2024 2:59:23 AM
 *  Author: Demiana Younes
 */ 

#include "StdTypes.h"

#include "Queue_Interface.h"
#include "Queue_Config.h"
#include "Queue_Private.h"



void CircularQueue_Init(CircularQueue_type*Queue)
{
	Queue->Front=FRONT_START;
	Queue->Rear=REAR_START;
}

static CircularQueue_Status_type IsFull(CircularQueue_type*Queue)
{
	CircularQueue_Status_type Queue_status=QUEUE_DONE;
	if(((Queue->Rear+1)%QUEUE_SIZE)==Queue->Front)
	{
		Queue_status=QUEUE_FULL;
	}
	return Queue_status;
}

static CircularQueue_Status_type IsEmpty(CircularQueue_type*Queue)
{
	CircularQueue_Status_type Queue_status=QUEUE_DONE;
	if((Queue->Front==FRONT_START) && (Queue->Rear==REAR_START))
	{
		Queue_status=QUEUE_EMPTY;
	}
	return Queue_status;
}

void Enqueue(CircularQueue_type*Queue, u8 Copy_u8Data)
{
	if(IsFull(Queue)==QUEUE_FULL)
	{
		return;
	}
	else if(IsEmpty(Queue)==QUEUE_EMPTY)
	{
		Queue->Rear=0;
	}
	else
	{
		Queue->Rear=(Queue->Rear+1)%QUEUE_SIZE;
	}
	Queue->Data[Queue->Rear]=Copy_u8Data;
}

void DeQueue(CircularQueue_type*Queue, u8*Copy_u8Data)
{
	if(IsEmpty(Queue)==QUEUE_EMPTY)
	{
		return;
	}
	else if(Queue->Front==Queue->Rear)
	{
		Queue->Front=FRONT_START;
		Queue->Rear=REAR_START;
	}
	else
	{
		Queue->Front=(Queue->Front+1)%QUEUE_SIZE;
	}
	*Copy_u8Data=Queue->Data[Queue->Front];
}