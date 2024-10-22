/*
 * EmbeddedAdvancedTasks.c
 *
 * Created: 10/21/2024 4:32:56 PM
 * Author : Demiana
 */ 

#include "StdTypes.h"

#include "DIO_Interface.h"
#include "TrafficLight_Interface.h"



int main(void)
{
    /* Replace with your application code */
	TracfficLight_voidInit();
    while (1) 
    {
		TracfficLight_voidRunnable();
    }
}

