

#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_

typedef enum{
	Black=0,
	White,
	Red,
	Lime,
	Blue,
	Yellow,
	Cyan,
	Magenta,
	Silver,
	Gray,
	Maroon,
	Olive,
	Green,
	Purple,
	Teal,
	Navy
}RGB_Color_type;


void RGB_Runnable(void);
void RGB_SetColour(RGB_Color_type Color);



#endif /* RGB_INTERFACE_H_ */