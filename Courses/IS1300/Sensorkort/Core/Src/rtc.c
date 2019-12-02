/**
 ******************************************************************************
 * File Name          : RTC.c
 * Description        : This file provides code for the configuration
 *                      of the RTC instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_POS1;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Enable Calibration
	 */
	if (HAL_RTCEx_SetCalibrationOutPut(&hrtc, RTC_CALIBOUTPUT_1HZ) != HAL_OK)
	{
		Error_Handler();
	}

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(rtcHandle->Instance==RTC)
	{
		/* USER CODE BEGIN RTC_MspInit 0 */

		/* USER CODE END RTC_MspInit 0 */
		/* RTC clock enable */
		__HAL_RCC_RTC_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**RTC GPIO Configuration
    PB2     ------> RTC_OUT_CALIB 
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF0_RTC_50Hz;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN RTC_MspInit 1 */

		/* USER CODE END RTC_MspInit 1 */
	}
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

	if(rtcHandle->Instance==RTC)
	{
		/* USER CODE BEGIN RTC_MspDeInit 0 */

		/* USER CODE END RTC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_RTC_DISABLE();

		/**RTC GPIO Configuration
    PB2     ------> RTC_OUT_CALIB 
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

		/* USER CODE BEGIN RTC_MspDeInit 1 */

		/* USER CODE END RTC_MspDeInit 1 */
	}
} 

/* USER CODE BEGIN 1 */

/*
@brief rtc_set_time, sets the RTC according to user input over USB and UART.
@param void, no parameters
@return void, no return value
 */
void rtc_set_time(void){
	usb_send_data("Set the time \"HHMMSS\"");
	uint8_t * user_set_time = rtc_char_to_int(usb_get_data());

	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	/** Initialize RTC and set the Time and Date
	 */
	if(user_set_time[0] <= 23 && user_set_time[1] <= 59 && user_set_time[2] <= 59) {
		sTime.Hours = user_set_time[0];
		sTime.Minutes = user_set_time[1];
		sTime.Seconds = user_set_time[2];
		sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		sTime.StoreOperation = RTC_STOREOPERATION_RESET;
		if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
		sDate.WeekDay = RTC_WEEKDAY_MONDAY;
		sDate.Month = RTC_MONTH_JANUARY;
		sDate.Date = 1;
		sDate.Year = 0;

		if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
	} else {
		Error_Handler();
	}

	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // Write to backup register
}

/*
@brief rtc_get_time, Fetches the current time from RTC time and date registers.
@param void, no parameters
@return time, the current time as a string.
 */
char * rtc_get_time() {

	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;

	static char time[10];

	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	/* Display time Format: hh:mm:ss */
	sprintf((char*)time,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);

	return time;
}

/*
@brief rtc_char_to_int, helper function to convert char input from user to uint8.
@param void, no parameters
@return time, the current time as a pointer to uint8 array.
 */
uint8_t * rtc_char_to_int(char string[]) {
	char string_arg[6];
	strncpy(string_arg, string, 6);

	static uint8_t time[3];

	int i;

	for(i = 0; i < 3; i++) {
		time[i] = ((((uint8_t)string_arg[i*2] - 0x30) * 10) + (((uint8_t)string_arg[i*2+1])) - 0x30); // convert to uint8 and sum
	}

	return time;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
