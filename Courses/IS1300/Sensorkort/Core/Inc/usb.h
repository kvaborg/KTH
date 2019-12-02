/**
 *****************************************************
 @brief usb, Header file for USB communication
 @file usb.h
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Header file for USB communication
 *****************************************************
 */

#ifndef USB_H
#define USB_H
#endif

#include "stdint.h"
#include "string.h"
#include "usart.h"

void usb_send_data(char * data);
char * usb_get_data(void);
