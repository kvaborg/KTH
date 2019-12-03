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

void test_rtc_set_time() {
	rtc_set_time();
}

void test_rtc_char_to_int() {
	rtc_char_to_int(time);
}
