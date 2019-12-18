/**
 *****************************************************
 @brief test_rtc, Header file for RTC test functions
 @file usb.c
 @author Alexander Borg
 @version 1.0
 @date 29-November-2019
 *****************************************************
 */

#include "../Inc/test_rtc.h"

char time[] = "100000";

/**
@brief test_rtc_set_time, tests rtc_set_time function.
@brief Success or Fail message sent over serial USB.
@param void, no parameters
@return void, no return value
 */
void test_rtc_set_time() {
	rtc_set_time();
}

/**
@brief test_rtc_char_to_int, tests rtc_char_to_int function.
@brief Sends the time as a string over seiral USB.
@param void, no parameters
@return void, no return value
 */
void test_rtc_char_to_int() {
	usb_send_data((char *)rtc_char_to_int(time));
}
