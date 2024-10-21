#include "StdTypes.h"
#include "MemMap.h"

#include "Timer_Interface.h"
#include "DIO_Interface.h"
#include "Ultrasonic_Interface.h"
#include "Ultrasonic_Private.h"
#include "Ultrasonic_Cfg.h"

#define F_CPU  8000000
#include <util/delay.h>

static volatile u8 flag;
static volatile u16 t1,t2;
static volatile u8 c=0;

/*for 4 ultrasonic*/
//volatile DIO_Pin_type TRIG_PIN ;

void ULTRASONIC_Init(void)
{
	/*you need to init timer1 in normal mode
	 *open global interrupt
	 *Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	 GLOBAL_ENABLE();
	 */
	Timer1_ICU_SetCallBack(ULTRASONIC_FUNC);
}
static void ULTRASONIC_Trigger(void)
{
	/*for 4 ultrasonic*/
// 	DIO_WritePin(TRIG_PIN,HIGH);
// 	_delay_us(10);
// 	DIO_WritePin(TRIG_PIN,LOW);
	DIO_WritePin(TRIGGER_PIN,HIGH);
	_delay_us(10);
	DIO_WritePin(TRIGGER_PIN,LOW);
}
u8 ULTRASONIC_Distance_BusyWait(void)
{
	u16 time,distance;
	flag=0;
	TCNT1=0;
	ULTRASONIC_Trigger();
	Timer1_ICU_InterruptEnable();
	Timer1_InputCaptureEdge(RISING);
	while(flag<2);
	time=t2-t1;
	/*distance by cm  distance=(340(m\s)*((time(us)/1000000)(s))*100) (cm)
	*340 is velocity of sound  */
	distance=time/58; 
	_delay_ms(60);
	return distance;
}

ultrasonic_type ULTRASONIC_Distance_PeriodicCheck(u8*pdistance)
{
	u16 time;
	static u8 FlagStart=0;
	ultrasonic_type UltrasonicCheck=ULTRASONIC_NOK;
	if(FlagStart==0)
	{
		FlagStart=1;
		flag=0;
		/*first method do TCNT1=0 
		 --> TCNT1=0;
		 *second method do global variable in ISR function increment 
		 then multiple counter in register but remember that register in timer1 is 16 bit= 65536
		 to protected from overflow flag
		 --> time=t2-t1+((u32)c*65536)
		 */
		ULTRASONIC_Trigger();
		Timer1_ICU_InterruptEnable();
		Timer1_InputCaptureEdge(RISING);
	}
	if(flag==2)
	{
		time=t2-t1+((u32)c*65536);
		*pdistance=time/58; //distance by cm
		_delay_ms(60);
		FlagStart=0;
		c=0;
		UltrasonicCheck=ULTRASONIC_OK;
	}
	return UltrasonicCheck;
}

static void ULTRASONIC_FUNC(void)
{
	c++;
	if(flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if(flag==1)
	{
		t2=ICR1;
		Timer1_ICU_InterruptDisable();
		flag=2;
	}
}