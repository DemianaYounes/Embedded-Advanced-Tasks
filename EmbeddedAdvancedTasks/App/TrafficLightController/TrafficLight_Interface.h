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

void TrafficLight_voidRunnable(void);
void TrafficLight_voidInit(void);

#endif /* TRAFFICLIGHT_INTERFACE_H_ */