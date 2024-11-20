/*
 * Stack_Interface.h
 *
 * Created: 11/14/2024 4:20:48 AM
 *  Author: dell
 */ 


#ifndef STACK_INTERFACE_H_
#define STACK_INTERFACE_H_

typedef enum{
	STACK_EMPTY,
	STACK_DONE,
	STACK_FULL,
}Stack_Status_t;

Stack_Status_t Stack_Push(void(*LocalFptr)(void));
Stack_Status_t Stack_Pop(void);



#endif /* STACK_INTERFACE_H_ */