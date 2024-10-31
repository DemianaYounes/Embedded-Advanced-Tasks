/*
 * Queue_Private.h
 *
 * Created: 10/30/2024 2:58:52 AM
 *  Author: Demiana Younes
 */ 


#ifndef QUEUE_PRIVATE_H_
#define QUEUE_PRIVATE_H_

#define REAR_START      -1
#define FRONT_START     -1

static CircularQueue_Status_type IsFull(CircularQueue_type*Queue);
static CircularQueue_Status_type IsEmpty(CircularQueue_type*Queue);



#endif /* QUEUE_PRIVATE_H_ */