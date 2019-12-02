/**
 *****************************************************
 @brief Display, display (LCD and Backlight) program
 @file display.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for Display
 *****************************************************
 */

#include "display.h"

/*
@brief display_time, prints the current time on the LCD.
@param void, no parameters
@return void, no return value
*/

void display_time() {
	char * time = rtc_get_time();
	lcd_set_pos(LINE1);
	lcd_write_string((char *)time);
}
