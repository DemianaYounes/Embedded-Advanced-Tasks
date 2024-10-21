
#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

typedef enum{
	ULTRASONIC_OK,
	ULTRASONIC_NOK
	}ultrasonic_type;

void ULTRASONIC_Init(void);
u8 ULTRASONIC_Distance_BusyWait(void);
ultrasonic_type ULTRASONIC_Distance_PeriodicCheck(u8*pdistance);



#endif /* ULTRASONIC_INTERFACE_H_ */