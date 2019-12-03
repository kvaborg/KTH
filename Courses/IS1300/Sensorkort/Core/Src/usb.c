/**
 *****************************************************
 @brief Usb, USB communication
 @file usb.c
 @author Alexander Borg
 @version 1.0
 @date 29-November-2019
 @brief Source code for USB communication
 *****************************************************
 */

#include "usb.h"

/*
@brief usb_send_data, sends an amount of data in blocking mode using UART over USB.
@param data, the data to send
@return void, no return value
*/
void usb_send_data(char * data) {
	char * data_terminator = "\n\r";
	char * buffer = strcat(data, data_terminator);

	HAL_UART_Transmit(&huart5, (uint8_t *)buffer, strlen(buffer), 100);
}

/*
@brief usb_get_data, receives an amount of data in blocking mode using UART over USB
@param void, no parameters
@return buffer, a pointer to an array of length 6 with the data received.
*/
char * usb_get_data() {

	static char buffer[6];
	HAL_UART_Receive(&huart5, (uint8_t *)buffer, 6, 10000);

	return buffer;
}
