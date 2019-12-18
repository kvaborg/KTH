/**
 *****************************************************
 @brief LCD Header file
 @file lcd.h
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Header file for LCD
 *****************************************************
 */

#ifndef LCD_H
#define LCD_H
#endif

#include "spi.h"
#include <stdint.h>

#define LINE1	0
#define LINE2	LINE1+0x20
#define LINE3	LINE1+0x40
#define	LINE4 	LINE1+0x60

#define LCD_HOME_L1	0x80

#define ROMA		0x00
#define ROMB		0x04
#define ROMC		0x0C

#define DISPLAY_ON 	0x04
#define DISPLAY_OFF 0x03
#define BLINK_ON	0x01
#define BLINK_OFF	0x06
#define CURSOR_ON	0x02
#define CURSOR_OFF	0x05

#define MAX_BUFFER_SIZE 3

void lcd_init(void);
void lcd_write_data(uint8_t);
void lcd_write_instr(uint8_t);
void lcd_clear(void);
void lcd_set_pos(uint8_t);
void lcd_write_char(int8_t);
void lcd_write_string(char *);
void lcd_on_off(uint8_t);
void lcd_set_contrast(uint8_t);
void lcd_set_ROM(uint8_t);
