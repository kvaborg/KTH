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

uint8_t green[] = "Green";
uint8_t red[] = "Red";
uint8_t white[] = "White";

/*
@brief test_backlight_set_color, tests the backlight_set_color function
@param void, no parameters
@return void, no return value
*/
void test_backlight_set_color() {
	backlight_set_color(white);
	HAL_Delay(1000);
}
