#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "WDT_Interface.h"
#include "WDT_Private.h"
#include "WDT_Cfg.h"

void WDT_Set(TimeOut_t time)
{
	u8 WDT_Value=0x08;
	WDT_Value|=time;
	cli();
	WDTCR|=(1<<WDE)|(1<<WDTOE);
	WDTCR=WDT_Value;
	sei();
}
void WDT_Stop(void)
{
	WDTCR=(1<<WDE)|(1<<WDTOE);
	WDTCR=0;
}