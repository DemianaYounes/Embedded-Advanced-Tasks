/*
 * Graphical_LCD_Interface.h
 *
 * Created: 11/3/2024 2:59:43 AM
 *  Author: Demiana Younes
 */ 


#ifndef GRAPHICAL_LCD_INTERFACE_H_
#define GRAPHICAL_LCD_INTERFACE_H_

void GLCD_voidInit(void);
void GLCD_voidWriteString(u8 Copy_u8PageNum,u8 Copy_u8Colums,u8*STR);
void GLCD_voidWriteChar(u8 Copy_u8PageNum, u8 Copy_u8Column, u8 Local_u8Character);
void GLCD_voidClear(void);
void GLCD_voidClearPage(u8 Copy_u8PageNum);
void GLCD_voidClearDot(u8 Copy_u8PageNum,u8 Copy_u8Column);
void GLCD_voidClearChar(u8 Copy_u8PageNum,u8 Copy_u8Column);
void GLCD_voidWriteNumber(u8 Copy_u8PageNum,u8 Copy_u8Column,u32 Copy_u32Num);
void GLCD_voidDrawBox(u8 Copy_u8StartWidth,u8 Copy_u8EndWidth,u8 Copy_u8StartPage,u8 Copy_u8EndPage);
void GLCD_voidClearBox(u8 Copy_u8StartWidth,u8 Copy_u8EndWidth,u8 Copy_u8StartPage,u8 Copy_u8EndPage);
void GLCD_voidWriteDot(u8 Copy_u8PageNum,u8 Copy_u8Column);
void GLCD_voidetPixel(u8 copy_u8X,u8 Copy_u8Y);
/*Bird Function*/
void GLCD_voidPrintBird(u8 Copy_u8PageNum, u8 Copy_u8Column);
void GLCD_voidDrawSadFace(u8 Copy_u8Column,u8 Copy_u8PageNum);
void GLCD_voidCryMoving(u8 Copy_u8Column,u8 Copy_u8PageNum);
void GLCD_voidClearBird(u8 Copy_u8PageNum, u8 Copy_u8Column);
void GLCD_voidBigBird(u8 Copy_u8Column,u8 Copy_u8PageNum);
void GLCD_voidBigBirdMoving(u8 Copy_u8Column,u8 Copy_u8PageNum);

#endif /* GRAPHICAL_LCD_INTERFACE_H_ */