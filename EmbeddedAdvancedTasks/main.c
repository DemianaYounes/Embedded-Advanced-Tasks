/*
 * EmbeddedAdvancedTasks.c
 *
 * Created: 10/21/2024 4:32:56 PM
 * Author : Demiana
 */ 

#define F_CPU 8000000
#include <util/delay.h>
#include "StdTypes.h"

#include "TrafficLight_Interface.h"
#include "EventBased_Interface.h"


#define TRAFFIC_LIGHT    0
#define EVENT_BASED      2
#define APPLICATION      EVENT_BASED

#if APPLICATION == TRAFFIC_LIGHT
int main(void)
{
    /* Replace with your application code */
	TrafficLight_voidInit();
    while (1) 
    {
		TrafficLight_voidRunnable();
    }
}

#elif APPLICATION==EVENT_BASED
int main()
{
	EventBased_Init();
	while(1)
	{
		EventBased_Runnable();
	}
}
#endif
