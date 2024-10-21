#include "StdTypes.h"

#include "ADC_Interface.h"
#include "Sensors_Interface.h"
#include "Sensors_Private.h"
#include "Sensors_Cfg.h"


/* return temperture*10 */
u16 TEMP_Read(void)
{
	u16 volt,temp;
	volt=ADC_VoltRead(LM35_CH);
	/*equation of lm35 is volt=mv/10
	*temp=volt (mv)/10;
	*i will return the temperature but multiple in 10 to take the more accuracy  
	*/
	temp=volt;
	return temp;
}

/*return pressure measure by (mkpa) and return pressure *10  */
u16 MPX_4115_()
{
	u16 ADC_Value,MPX_Pressure_Value;
	ADC_Value=ADC_Read(MPX4115_CH);
	MPX_Pressure_Value=(((u32)(ADC_Value-55)*1000)/921)+150;
	return MPX_Pressure_Value;
}