/**
 *****************************************************
 @brief test_backlight, backlight tests
 @file test_backlight.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for for backlight tests
 *****************************************************
 */

#include "test_backlight.h"

char green[] = "Green";
char red[] = "Red";
char white[] = "White";

/*
@brief test_backlight_set_color, tests the backlight_set_color function
@param void, no parameters
@return void, no return value
*/
void test_backlight_set_color() {
	set_color(white);
	HAL_Delay(1000);
}
