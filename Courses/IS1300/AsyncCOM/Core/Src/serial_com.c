#include "serial_com.h"

#define BUFFERSIZE 22

ITStatus UartReady = RESET;
uint8_t Buffer[] = "Hello World interrupt!";


void communicate(void)
{
//	/* Start transmission process */
//	if (HAL_UART_Transmit_IT(&huart5, (uint8_t *)Buffer, BUFFERSIZE) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	/* Wait for the end of the transfer */
//	while (UartReady != SET)
//	{
//
//	}
//	/* Reset transmission flag */
//	UartReady = RESET;

	while(1)
	{

		/* Start transmission process */
		if (HAL_UART_Transmit_IT(&huart5, (uint8_t *)Buffer, BUFFERSIZE) != HAL_OK)
		{
			Error_Handler();
		}
		/* Wait for the end of the transfer */
		while (UartReady != SET)
		{

		}
		/* Reset transmission flag */
		UartReady = RESET;

		/* Put UART peripheral in reception process */
		if (HAL_UART_Receive_IT(&huart5, (uint8_t *)Buffer, BUFFERSIZE) != HAL_OK)
		{
			Error_Handler();
		}
		/* Wait for the end of the transfer */
		while (UartReady != SET)
		{

		}

		/* Reset transmission flag */
		UartReady = RESET;
	}


}

/**
 * @brief Tx transfer complete callback
 * @param UartHanlde: UART handle
 * @note This example shows a simple way to report end of IT Tx transfer, and
 * 		you can add your own implementation
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}

/**
 * @brief Rx transfer complete callback
 * @param UartHanlde: UART handle
 * @note This example shows a simple way to report end of IT Rx transfer, and
 * 		you can add your own implementation
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}
