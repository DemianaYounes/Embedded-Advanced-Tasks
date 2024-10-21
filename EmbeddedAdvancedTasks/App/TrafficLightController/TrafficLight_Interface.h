/*
 * TrafficLight_Interface.h
 *
 * Created: 10/21/2024 4:52:31 PM
 *  Author: Demiana Younes
 */ 


#ifndef TRAFFICLIGHT_INTERFACE_H_
#define TRAFFICLIGHT_INTERFACE_H_

typedef enum{
	STACK_EMPTY,
	STACK_DONE,
	STACK_FULL,
	}Stack_Status_t;
	
typedef enum{
	RED,
	YELLOW,
	GRREN,
	}TrafficLight_Status_t;

void TracfficLight_voidRunnable(void);
void TracfficLight_voidInit(void);

#endif /* TRAFFICLIGHT_INTERFACE_H_ */