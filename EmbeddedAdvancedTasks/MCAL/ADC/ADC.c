
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Cfg.h"

u16 volt_ref;
static u8 ADC_ReadFlag=0;

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/*Vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		volt_ref=AREE;
		break;
		case VREF_AVCC:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		volt_ref=5000;
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		volt_ref=2560;
		break;
	}
	/*Clock*/
	ADCSRA=ADCSRA&0xf8;
// 	if(scaler>7)  //saturation 
// 	{
// 		scaler=7;
// 	}
	scaler=scaler&0x07; //truncation
	ADCSRA=ADCSRA|scaler;
	/*Read Adjusted */
	CLR_BIT(ADMUX,ADLAR);
	/*ADC_Enable*/
	SET_BIT(ADCSRA,ADEN);
}
void ADC_StartConversion(ADC_Channel_type channel)
{
	if(ADC_ReadFlag=0)
	{
		/* select ch using mux*/
		ADMUX=ADMUX&0xE0;
		ADMUX=ADMUX|channel;
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ADC_ReadFlag=1;
	}
}

u8 ADC_GetReadPeroidicCheck(u16*pdata)
{
	/*check if reading end*/
	if(!READ_BIT(ADCSRA,ADSC))
	{
		*pdata=ADC;
		ADC_ReadFlag=0;
		return 1;
	}
	return 0;
}

u16 ADC_GetRead(void)
{
	/*wait until end     busy wait or blocking*/
	while(READ_BIT(ADCSRA,ADSC));
	ADC_ReadFlag=1;
	/* get reading from 2 registers*/
	return ADC;
}

u16 ADC_GetReadNoBlock(void)
{
	/* get reading from 2 registers*/
	return ADC;
}

u16 ADC_Read(ADC_Channel_type channel)
{
	u16 adc;
	/* select ch using mux*/
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|channel;
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait tell end busy wait or blocking*/
	while(READ_BIT(ADCSRA,ADSC));  //busy waiting
	/*get reading from two register*/
	//adc=(((u16)ADCH<<8)|(u16)ADCL);
	adc=ADC;
	return adc;
}

u8 ADC_Scale(u16 ADC_Value)
{
	u8 scale;
	scale=(ADC_Value/1023.0)*100;
	return scale;
}

// u8 ADC_Volt(u16 value)
// {
// 	u16 volt;
// 	volt=((value*5)/1023.0);
// 	return volt;
// }



u16 ADC_ReadVolt(ADC_Channel_type channel)
{
	u16 volt,value;
	value=ADC_Read(channel);
	/*the value of int in processor is 2 byte if multiple 5000 *1000= 5 million
	*and the maximum value of u16 is 65536 truncation will happen in this equation 
	*you can solve this problem by casting 5000 to u32 (4 bytes)
	*we multiple in 5000 to calculate the result by (mv)*/
	volt=((value*(u32)volt_ref)/1024.0);
	return volt;
}