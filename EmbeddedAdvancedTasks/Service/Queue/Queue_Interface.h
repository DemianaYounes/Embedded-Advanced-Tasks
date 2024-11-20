/*
 * Queue_Interface.h
 *
 * Created: 10/30/2024 2:58:38 AM
 *  Author: Demiana Younes
 */ 


#ifndef QUEUE_INTERFACE_H_
#define QUEUE_INTERFACE_H_

#include "Queue_Config.h"

typedef struct{
	u8 Data[QUEUE_SIZE];
	s8 Front;
	s8 Rear;
	}CircularQueue_type;

typedef enum{
	QUEUE_FULL,
	QUEUE_EMPTY,
	QUEUE_DONE
	}CircularQueue_Status_type;
	
void CircularQueue_Init(CircularQueue_type*Queue);
void Enqueue(CircularQueue_type*Queue, u8 Copy_u8Data);
void DeQueue(CircularQueue_type*Queue, u8*Copy_u8Data);
CircularQueue_Status_type IsEmpty(CircularQueue_type*Queue);

#endif /* QUEUE_INTERFACE_H_ */