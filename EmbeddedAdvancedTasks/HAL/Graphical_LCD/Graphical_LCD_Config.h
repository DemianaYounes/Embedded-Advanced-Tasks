/*
 * Graphical_LCD_Config.h
 *
 * Created: 11/3/2024 3:00:02 AM
 *  Author: Demiana Younes
 */ 


#ifndef GRAPHICAL_LCD_CONFIG_H_
#define GRAPHICAL_LCD_CONFIG_H_

#define GLCD_DATA_PORT			PA	/* Define data port for GLCD */

#define GLCD_RS		            PINB3 	/* Define control pins */
#define GLCD_RW		            PINB4
#define GLCD_EN		            PINB5
#define GLCD_CS1	         	PINB0
#define GLCD_CS2	         	PINB1
#define GLCD_RST	         	PINB2

#define GLCD_TOTAL_PAGE			    8



#endif /* GRAPHICAL_LCD_CONFIG_H_ */