/**
 *****************************************************
 @brief Serial Communication, Serial communication program.
 @file test_usb.c
 @author Alexander Borg
 @version 1.0
 @date 29-November-2019
 @brief Source code for USB and BT communication.
 *****************************************************
 */

#include <serial_com.h>

/**
@brief com_all, sends all processed data in blocking mode using UART over USB and bluetooth.
@param void, no return value
@return void, no return value
 */
void com_all() {
	if(gTime.Seconds % 10 == 0 && gTime.SubSeconds < 50) {
		bt_send_data((char *)hts_get_hum_temp());
	}
}
