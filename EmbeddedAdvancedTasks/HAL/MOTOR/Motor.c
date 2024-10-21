
#include "StdTypes.h"
/*Includes From MCAL*/
#include "DIO_Interface.h"
/*Includes From HAL*/
#include "Motor_Interface.h"
#include "Motor_Cfg.h"

void Motor_Init()
{
	
}
void MOTOR_Stop(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
	DIO_WritePin(MotorPinsArray[motor][IN2],LOW);
}
void MOTOR_CW(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN1],HIGH);
	DIO_WritePin(MotorPinsArray[motor][IN2],LOW);
}
void MOTOR_CCW(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
	DIO_WritePin(MotorPinsArray[motor][IN2],HIGH);
}