#include "StdTypes.h"

#include "MemMap.h"

#include "RGB_Interface.h"
#include "RGB_Cfg.h"
#include "RGB_Private.h"
#define F_CPU  8000000
#include <util/delay.h>


void RGB_Runnable(void)
{
	u8 i;
	for(i=0;i<14;i++)
	{
		OCR1A=RGB_RedColors[i][0];
		OCR1B=RGB_RedColors[i][1];
		OCR0=RGB_RedColors[i][2];
		_delay_ms(1000);
	}
}

void RGB_SetColour(RGB_Color_type Color)
{
	OCR1A=RGB_BasicsColors[Color][0];
	OCR1B=RGB_BasicsColors[Color][1];
	OCR0=RGB_BasicsColors[Color][2];
}