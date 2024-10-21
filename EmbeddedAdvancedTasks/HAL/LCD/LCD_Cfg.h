

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/******** _4_BIT or _8_BIT ********/
#define LCD_MODE   _4_BIT

/*Configuration for _4_bit */
#define D4  PINA3
#define D5  PINA4
#define D6  PINA5
#define D7  PINA6

/*Configuration for _8_BIT */
#define LCD_PORT   PA

/*Configuration for _4_bit and _8_BIT */
#define RS  PINA1
#define EN  PINA2



#endif /* LCD_CFG_H_ */