
#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_

typedef enum{
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4
	}Button_type;
typedef enum{
	PRESSED,
	NOT_PRESSED
	}Button_value;

void Button_Init(void);
Button_value Button_Pins(Button_type button);

#endif /* BUTTON_INTERFACE_H_ */