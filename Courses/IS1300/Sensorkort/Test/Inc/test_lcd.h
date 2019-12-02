/**
 *****************************************************
 @brief test_lcd, Header file for LCD test program
 @file lcd.h
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Header file for LCD test program
 *****************************************************
 */

#ifndef TEST_LCD_H
#define TEST_LCD_H
#endif

#include "gpio.h"
#include "lcd.h"

void test_lcd_init(void);
void test_lcd_clear(void);
void test_lcd_write_char(void);
void test_lcd_write_string(void);
void test_lcd_set_ROM(void);
void test_lcd_on_off(void);
void test_lcd_set_pos(void);
