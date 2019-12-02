/**
 *****************************************************
 @brief test, test-program
 @file test.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for main test program
 *****************************************************
 */

#include "../Inc/test.h"

/*
@brief test_program, main test program that runs tests for all components
@param void, no parameters
@return void, no return value
*/
void test_program() {
	//test_set_color();
	test_lcd_init();
	HAL_Delay(100);
//	test_rtc_string_to_int();
//	test_lcd_clear();
//	HAL_Delay(1000);
//	test_lcd_on_off();
//	HAL_Delay(1000);
//	test_lcd_set_ROM();
//	HAL_Delay(1000);
//	test_lcd_set_pos();
//	HAL_Delay(1000);
//	test_lcd_write_string();
//	HAL_Delay(5000);
//	test_lcd_write_char();
	test_rtc_set_time();
	while(1) {
		test_display_time();
	}


//	test_usb_get_data();
}
