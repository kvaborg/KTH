/**
 *****************************************************
 @brief Test ADC, ADC tests.
 @file test_adc.h
 @author Alexander Borg
 @version 1.0
 @date 12-December-2019
 @brief Source code for ADC tests.
 *****************************************************
 */

#include "../Inc/test_adc.h"

/**
@brief test_adc_get_value, tests the adc_get_value library function.
@brief ADC values sent over serial USB.
@param void, no parameters
@return void, no return value
 */
void test_adc_get_value() {
	int i;
	char adc_str[10];

	for(i = 0; i < 10; i++) {
		int val = adc_get_value();
		sprintf(adc_str, "%d", val);
		usb_send_data(adc_str);
		HAL_Delay(1000);
	}
}
