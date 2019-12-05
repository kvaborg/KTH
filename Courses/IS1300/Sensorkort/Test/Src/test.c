/**
 *****************************************************
 @brief test, main test program
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
	/* ADC TEST */
	test_adc_get_value();

	/* USB TEST */
	test_usb_send_data();
	HAL_Delay(1000);
	test_usb_get_data();
	HAL_Delay(10);

	/* LCD, DISPLAY AND BACKLIGHT TESTS */
	test_lcd_init();
	HAL_Delay(100);
	test_lcd_clear();
	HAL_Delay(100);
	test_lcd_on_off();
	test_lcd_clear();
	HAL_Delay(100);
	test_lcd_write_string();
	test_lcd_write_char();
	test_backlight_set_color();
	test_lcd_clear();
	test_rtc_set_time();
	while(1) {
		test_backlight_set_brightness();
		test_display_time();
	}



	//	test_usb_get_data();
}
