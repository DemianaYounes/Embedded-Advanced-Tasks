
#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/*********************************Pin Config*********************************/
/*M1*/
#define M1_IN1   PINA0
#define M1_IN2   PINA1
#define M1_EN    PINA1
/*M2*/
#define M2_IN1   PINA0
#define M2_IN2   PINA1
#define M2_EN    PINA1
/*M3*/
#define M3_IN1   PINA0
#define M3_IN2   PINA1
#define M3_EN    PINA1
/*M4*/
#define M4_IN1   PINA0
#define M4_IN2   PINA1
#define M4_EN    PINA1
/*********************************Config Method*********************************/
#define METHOD_TYPE   0
#if METHOD_TYPE==1
typedef struct{
	DIO_Pin_type IN1;
	DIO_Pin_type IN2;
	DIO_Pin_type EN;
	}MOTOR_Pins_type;
MOTOR_Pins_type MotorPinsArray[NUMBER_MOTORS]={
          //IN1    IN2   EN
		  /*MOTOR_1*/{M1_IN1,M1_IN2,M1_EN},
		  /*MOTOR_2*/{M2_IN1,M2_IN2,M2_EN},
		  /*MOTOR_3*/{M3_IN1,M3_IN2,M3_EN},
		  /*MOTOR_4*/{M4_IN1,M4_IN2,M4_EN}  
		  };
#elif METHOD_TYPE==0
DIO_Pin_type MotorPinsArray[NUMBER_MOTORS][MOTOR_PIN_NUMBERS]={
	//IN1    IN2   EN
	/*MOTOR_1*/{M1_IN1,M1_IN2,M1_EN},
	/*MOTOR_2*/{M2_IN1,M2_IN2,M2_EN},
	/*MOTOR_3*/{M3_IN1,M3_IN2,M3_EN},
	/*MOTOR_4*/{M4_IN1,M4_IN2,M4_EN}
};
#endif

#endif /* MOTOR_CFG_H_ */