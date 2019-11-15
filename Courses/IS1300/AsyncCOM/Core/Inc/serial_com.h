#ifndef SERIAL_COM_H
#define SERIAL_COM_H
#endif

#include "stdbool.h"
#include "usart.h"

void communicate(void);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
