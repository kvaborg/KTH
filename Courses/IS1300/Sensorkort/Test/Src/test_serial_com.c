/**
 *****************************************************
 @brief Test COM, Communication tests
 @file test_usb.c
 @author Alexander Borg
 @version 1.0
 @date 29-November-2019
 @brief Source code for USB and BT communication tests
 *****************************************************
 */

#include "../Inc/test_serial_com.h"

char * data = "Serial communication test!";

/**
@brief test_usb_send_data, tests the usb_send_data function
@param void, no parameters
@return void, no parameters
*/
void test_usb_send_data() {
	usb_send_data(data);
}

/**
@brief test_usb_get_data, tests the usb_get_data function
@brief Sends the data over serial USB on success.
@param void, no parameters
@return void, no parameters
*/
void test_usb_get_data(void) {
	char * data = usb_get_data();
	usb_send_data((char *)data);
}

/**
@brief test_bt_send_data, tests the bt_send_data function.
@brief Sends the data over serial bluetooth on success.
@param void, no parameters
@return void, no parameters
*/
void test_bt_send_data(void) {
	bt_send_data(data);
}
