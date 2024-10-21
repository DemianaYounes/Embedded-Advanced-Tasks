

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Init(void);
void LCD_WriteString(u8*str);
void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHexa(u8 num);
void LCD_WriteChar(u8 ch);
void LCD_SetCurser(u8 line ,u8 cell);
void LCD_Clear(void);
void LCD_CustomChar(u8 loc,u8*pattern);
void LCD_WriteHexa_Method2(u8 num);


#endif /* LCD_INTERFACE_H_ */