
#include "StdTypes.h"
/*Include From MCAL*/
#include "DIO_Interface.h"
/*Include From HAL*/
#include "Button_Interface.h"
#include "Button_Cfg.h"

void Button_Init(void)
{
	/*Button must be connect with input pull up 
	*or connect external pull up or pull down
	*to connect the internal pull up resistor must do DDR register 0x00
	* and PORT register 0xff all this configuration handled in DIO by doing 
	*the pin INPULL
	*return value if zero means that the button is pressed
	*if one the button is not pressed
	*/
}

Button_value Button_Pins(Button_type button)
{
	Button_value value=NOT_PRESSED;
	switch(button)
	{
		case BUTTON_1:
		value=DIO_ReadPin(BUTTON1_PIN);
		break;
		case BUTTON_2:
		value=DIO_ReadPin(BUTTON2_PIN);
		break;
		case BUTTON_3:
		value=DIO_ReadPin(BUTTON3_PIN);
		break;
		case BUTTON_4:
		value=DIO_ReadPin(BUTTON4_PIN);
		break;
	}
	return value;
}