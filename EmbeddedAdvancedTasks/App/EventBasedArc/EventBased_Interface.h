/*
 * EventBased_Interface.h
 *
 * Created: 10/30/2024 2:53:43 AM
 *  Author: Demiana Younes
 */ 


#ifndef EVENTBASED_INTERFACE_H_
#define EVENTBASED_INTERFACE_H_

/**
 * @brief Initializes the event-driven architecture components, configuring the 
 *        digital I/O, external interrupts, timers, and the event queue.
 *
 *        Sets up DIO, defines the trigger for external interrupts, and initializes
 *        Timer1 for generating periodic timer events. Registers callback functions
 *        for handling external and timer-based interrupts and enables global 
 *        interrupts.
 *
 * @return None
 */
void EventBased_Init(void);

/**
 * @brief Processes queued button events by reading from the circular queue.
 *        Dequeues an event and performs actions like toggling specific pins
 *        based on the event type. If the queue is empty, it sets a default pin.
 *
 * @return None
 */
void EventBased_Runnable(void);


#endif /* EVENTBASED_INTERFACE_H_ */