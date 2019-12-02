/**
 *****************************************************
 @brief Test USB, USB communication tests
 @file test_usb.c
 @author Alexander Borg
 @version 1.0
 @date 29-November-2019
 @brief Source code for USB communication tests
 *****************************************************
 */

#include "test_usb.h"

char * data = "Serial communication test!";

/*
@brief test_usb_send_data, tests the usb_send_data function
@param void, no parameters
@return void, no parameters
*/
void test_usb_send_data() {
	usb_send_data(data);
}

/*
@brief test_usb_get_data, tests the usb_get_data function
@param void, no parameters
@return void, no parameters
*/
void test_usb_get_data(void) {
	char * data = usb_get_data();
	usb_send_data((char *)data);
}
