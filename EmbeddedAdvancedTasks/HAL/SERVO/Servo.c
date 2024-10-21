#include "StdTypes.h"
#include "MemMap.h"

#include "Timer_Interface.h"
#include "Servo_Interface.h"
#include "Servo_Cfg.h"
#include "Servo_Private.h"

void SERVO_Init(void)
{
	/*set the start value of SERVO_REGISTER*/
	SERVO_REGISTER=START_VALUE_IN_KIT;
	/*you can use timer1 but set mode fast mode OCR1A top or OCR1B top or ICU mode
	 * to set frequency 20000 (from data sheet servo) but in register 19999
	 *ex:
	 *Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);     
	 *Timer1_OCRB1Mode(OCRB_NON_INVERTING);  to change in duty cycle from real motor 500 to 2500 or proteus from 1000 to 2000
	 *OCR1A=19999;    to set frequeny 50hz (T(total)=20000
	 */
}
void SERVO_SetAngleInProteus(u8 Copy_u8Angle)
{
	/*  interpolation 
	 *this servo start from 1000    2000
	 *     angle start from  0       180
	 *slope=(2000-1000)/(180-0)=1000/180
	 *y-y1=slope(x-x1)  -->  OCR1B-OCR1B1=slope(angle-angle1)
	 * OCR1B=(1000/180)(180-0)+999   --> OCR1B=(((u32)Copy_u8Angle*1000)/(u32)180)+999
	 */
	if(Copy_u8Angle>180)
	{
		Copy_u8Angle=180;
	}
	SERVO_REGISTER=(((u32)Copy_u8Angle*1000)/(u32)180)+999;
	/*to get more accuracy in angle you have to method
	 * 1-->add 90 to equation OCR1B=(((u32)Copy_u8Angle*1000+90)/(32)180)+999;
	 * 2-->do array and put the values of OCR1B  (the best method)
	 */
}
void SERVO_SetAngle(u8 Copy_u8Angle)
{
	/*this servo start from 500     2500
	 *     angle start from  0       180
	 *slope=(2500-500)/(180-0)=2000/180
	 *y-y1=slope(x-x1)  -->  OCR1B-OCR1B1=slope(angle-angle1)
	 * OCR1B=(2000/180)(180-0)+499   --> OCR1B=(((u32)Copy_u8Angle*2000)/(u32)180)+499
	 */
	if(Copy_u8Angle>180)
	{
		Copy_u8Angle=180;
	}
	SERVO_REGISTER=(((u32)Copy_u8Angle*2000)/(u32)180)+499;
	/*to get more accuracy in angle you have to method
	 * 1-->add 90 to equation OCR1B=(((u32)Copy_u8Angle*1000+90)/(32)180)+999;
	 * 2-->do array and put the values of OCR1B  (the best method)
	 */
}
