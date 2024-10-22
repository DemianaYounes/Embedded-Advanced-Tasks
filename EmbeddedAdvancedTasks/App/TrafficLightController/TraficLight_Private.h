/*
 * TraficLight_Private.h
 *
 * Created: 10/21/2024 4:53:08 PM
 *  Author: Demiana Younes
 */ 


#ifndef TRAFICLIGHT_PRIVATE_H_
#define TRAFICLIGHT_PRIVATE_H_

#define STACK_POINTER_INIT    -1

static Stack_Status_t Stack_Push(void(*LocalFptr)(void));
static Stack_Status_t Stack_Pop(void);
static void Stack_CallBack(void);

static void Red_Led(void);
static void Yellow_Led(void);
static void Green_Led(void);



#endif /* TRAFICLIGHT_PRIVATE_H_ */
