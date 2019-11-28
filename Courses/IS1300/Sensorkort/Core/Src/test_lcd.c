/**
 *****************************************************
 @brief test_lcd, LCD test program
 @file lcd.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for LCD test program
 *****************************************************
 */

#include "test_lcd.h"

uint8_t ch = 'a';
uint8_t string[] = "HLO WORLD!";

/*
@brief test_lcd_init, tests lcd_init function
@param void, no parameters
@return void, no return value
*/
void test_lcd_init() {
	lcd_init();
}

/*
@brief test_lcd_clear, tests lcd_clear function
@param void, no parameters
@return void, no return value
*/
void test_lcd_clear() {
	lcd_clear();
}

/*
@brief test_lcd_write_char, tests lcd_write_char function
@param void, no parameters
@return void, no return value
*/
void test_lcd_write_char() {
	lcd_write_char(ch);
}

/*
@brief test_lcd_write_string, tests lcd_write_char function
@param void, no parameters
@return void, no return value
*/
void test_lcd_write_string(void) {
	lcd_write_string(string);
}

/*
@brief test_lcd_set_ROM, tests lcd_set_ROM function
@param void, no parameters
@return void, no return value
*/
void test_lcd_set_ROM(void) {
	lcd_set_ROM(ROMA);
}

/*
@brief test_lcd_on_off, tests lcd_on_off function
@param void, no parameters
@return void, no return value
*/
void test_lcd_on_off(void) {
	lcd_on_off(DISPLAY_ON);
}

/*
@brief test_lcd_set_pos, tests lcd_set_pos function
@param void, no parameters
@return void, no return value
*/
void test_lcd_set_pos(void) {
	lcd_set_pos(LINE1);
}
