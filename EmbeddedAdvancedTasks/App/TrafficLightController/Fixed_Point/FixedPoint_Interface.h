/*
 * FixedPoint_Interface.h
 *
 * Created: 10/27/2024 12:12:39 AM
 *  Author: Demiana Younes
 */ 


#ifndef FIXEDPOINT_INTERFACE_H_
#define FIXEDPOINT_INTERFACE_H_

typedef u32 FixedPoint;

void FixedPoint_voidInit(void);
FixedPoint FixedPoint_Addition(float Copy_Num1,float Copy_Num2);
s32 FixedPoint_ConvertFixedPointToFloat(s32 Copy_Num);
s32 FixedPoint_Subtraction(float Copy_Num1,float Copy_Num2);
s32 FixedPoint_Multiplcation(float Copy_Num1,float Copy_Num2);
s32 FixedPoint_Division(float Copy_Num1,float Copy_Num2);

#endif /* FIXEDPOINT_INTERFACE_H_ */