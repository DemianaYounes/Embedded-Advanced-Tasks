/*
 * EventBased_Private.h
 *
 * Created: 10/30/2024 2:54:00 AM
 *  Author: Demiana Younes
 */ 


#ifndef EVENTBASED_PRIVATE_H_
#define EVENTBASED_PRIVATE_H_

#define BUTTON1_WITH_EXT_INT0      1
#define BUTTON2_WITH_TIMER_INT     2


/**
 * @brief Callback function triggered by the external interrupt (INT0).
 *
 *        Enqueues an event in the circular queue indicating that BUTTON1 
 *        was pressed, triggered by an external interrupt.
 *
 * @return None
 */
static void CallBack_INT0(void);

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
static void CallBack_Timer1(void);



#endif /* EVENTBASED_PRIVATE_H_ */