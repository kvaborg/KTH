/**
 *****************************************************
 @brief BT, Bluetooth  (BT) communication.
 @file bt.c
 @author Alexander Borg
 @version 1.0
 @date 12-December-2019
 @brief Source code for BT communication.
 *****************************************************
 */

#include "bt.h"

/**
@brief bt_send_data, sends an amount of data in blocking mode using UART over bluetooth.
@param char *, pointer to char array holding the data to send
@return void, no return value
*/
void bt_send_data(char * data) {
	HAL_UART_Transmit(&huart4, (uint8_t *)data, strlen(data), HAL_MAX_DELAY);
}
