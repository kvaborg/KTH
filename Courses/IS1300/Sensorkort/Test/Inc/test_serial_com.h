/**
 *****************************************************
 @brief Test Serial Com, Header file for Serial com tests.
 @file test_serial_com.h
 @author Alexander Borg
 @version 1.0
 @date 29-November-2019
 @brief Header file for USB and bluetooth serial communication tests
 *****************************************************
 */

#ifndef TEST_USB_H
#define TEST_USB_H
#endif

#include "usb.h"
#include "bt.h"
#include <stdint.h>

void test_usb_send_data(void);
void test_usb_get_data(void);
void test_bt_send_data(void);
