/*
 * TraficLight_Private.h
 *
 * Created: 10/21/2024 4:53:08 PM
 *  Author: Demiana Younes
 */ 


#ifndef TRAFICLIGHT_PRIVATE_H_
#define TRAFICLIGHT_PRIVATE_H_

#define STACK_POINTER_INIT    -1

static Stack_Status_t Stack_Push(u8 Copy_u8Data);
static Stack_Status_t Stack_Pop(u8* Copy_pu8Data);
static u8 Stack_u8GetCurrentState(void);
static void Stack_CallBack(void);



#endif /* TRAFICLIGHT_PRIVATE_H_ */