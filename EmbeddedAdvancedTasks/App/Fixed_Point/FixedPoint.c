/*
 * FixedPoint_Interface.c
 *
 * Created: 10/27/2024 12:10:51 AM
 *  Author: Demiana Younes
 */ 

#include "StdTypes.h"

#include "DIO_Interface.h"


#include "FixedPoint_Interface.h"
#include "FixedPoint_Private.h"
#include "FixedPoint_Cfg.h"


void FixedPoint_voidInit()
{
	
}

FixedPoint FixedPoint_Addition(float Copy_Num1,float Copy_Num2)
{
	
	FixedPoint Local_FloatNum1=FLOAT_TO_FIXED_POINT(Copy_Num1);
	FixedPoint Local_FloatNum2=FLOAT_TO_FIXED_POINT(Copy_Num2);
	FixedPoint Local_FloatSum=Local_FloatNum1+Local_FloatNum2;
	return Local_FloatSum;
}
s32 FixedPoint_ConvertFixedPointToFloat(s32 Copy_Num)
{
	return ((Copy_Num*10.0)/FP_SCALE);
}

s32 FixedPoint_Subtraction(float Copy_Num1,float Copy_Num2)
{
	
	FixedPoint Local_FloatNum1=FLOAT_TO_FIXED_POINT(Copy_Num1);
	FixedPoint Local_FloatNum2=FLOAT_TO_FIXED_POINT(Copy_Num2);
	s32 Local_FloatSub=Local_FloatNum1-Local_FloatNum2;
	return Local_FloatSub;
}

s32 FixedPoint_Multiplcation(float Copy_Num1,float Copy_Num2)
{
	FixedPoint Local_FloatNum1=FLOAT_TO_FIXED_POINT(Copy_Num1);
	FixedPoint Local_FloatNum2=FLOAT_TO_FIXED_POINT(Copy_Num2);
	FixedPoint Local_FloatMul=((u64)((u64)Local_FloatNum1 *Local_FloatNum2) >> FP_SHIFT);
	return Local_FloatMul;
}
s32 FixedPoint_Division(float Copy_Num1,float Copy_Num2)
{
	if(Copy_Num2==0)
	{
		return 0;
	}
	FixedPoint Local_FloatNum1=FLOAT_TO_FIXED_POINT(Copy_Num1);
	FixedPoint Local_FloatNum2=FLOAT_TO_FIXED_POINT(Copy_Num2);
	FixedPoint Local_FloatDiv=((u64)Local_FloatNum1<<FP_SHIFT)/Local_FloatNum2;
	return Local_FloatDiv;
}