

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#define MOTOR_PIN_NUMBERS  3
#define IN1  0
#define IN2  1
#define EN   2

typedef enum{
	M1,
	M2,
	M3,
	M4,
	NUMBER_MOTORS
}MOTOR_type;

void Motor_Init(void);
void MOTOR_Stop(MOTOR_type motor);
void MOTOR_CW(MOTOR_type motor);
void MOTOR_CCW(MOTOR_type motor);



#endif /* MOTOR_INTERFACE_H_ */