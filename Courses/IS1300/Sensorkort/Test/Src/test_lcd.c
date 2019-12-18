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

#include "../Inc/test_lcd.h"

/**
@brief test_lcd_init, tests lcd_init function.
@brief LCD turned on on success.
@param void, no parameters.
@return void, no return value.
 */
void test_lcd_init() {
	lcd_init();
}

/**
@brief test_lcd_clear, tests lcd_clear function.
@brief Clears the LCD on success.
@param void, no parameters.
@return void, no return value.
 */
void test_lcd_clear() {
	lcd_clear();
}

/**
@brief test_lcd_write_char, tests lcd_write_char function
@brief Writes one character to each line on success.
@param void, no parameters
@return void, no return value
 */
void test_lcd_write_char() {
	lcd_set_pos(LINE1);
	lcd_write_char('a');
	lcd_set_pos(LINE2);
	lcd_write_char('b');
	lcd_set_pos(LINE3);
	lcd_write_char('c');
	lcd_set_pos(LINE4);
	lcd_write_char('d');
	HAL_Delay(1000);
	test_lcd_clear();
}

/**
@brief test_lcd_write_string, tests lcd_write_char function.
@brief Writes a string to each line on success.
@param void, no parameters.
@return void, no return value.
 */
void test_lcd_write_string(void) {
	lcd_set_pos(LINE1);
	lcd_write_string("TEST LINE1");
	lcd_set_pos(LINE2);
	lcd_write_string("TEST LINE2");
	lcd_set_pos(LINE3);
	lcd_write_string("TEST LINE3");
	lcd_set_pos(LINE4);
	lcd_write_string("TEST LINE4");
	HAL_Delay(3000);
	test_lcd_clear();
}

/**
@brief test_lcd_set_ROM, tests lcd_set_ROM function
@param void, no parameters
@return void, no return value
 */
void test_lcd_set_ROM(void) {
	lcd_set_ROM(ROMA);
}

/**
@brief test_lcd_on_off, tests lcd_on_off function
@brief Turns the LCD off and on on success.
@param void, no parameters.
@return void, no return value.
 */
void test_lcd_on_off(void) {
	lcd_on_off(DISPLAY_OFF);
	HAL_Delay(1000);
	test_lcd_init();
	lcd_on_off(DISPLAY_ON);
	HAL_Delay(10);
}

/**
@brief test_lcd_set_pos, tests lcd_set_pos function
@brief Puts the cursoŕ on each line for 1 s on success.
@param void, no parameters
@return void, no return value
 */
void test_lcd_set_pos(void) {
	lcd_set_pos(LINE1);
	HAL_Delay(1000);
	lcd_set_pos(LINE2);
	HAL_Delay(1000);
	lcd_set_pos(LINE3);
	HAL_Delay(1000);
	lcd_set_pos(LINE4);
	HAL_Delay(1000);

}
