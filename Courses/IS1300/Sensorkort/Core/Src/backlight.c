/**
 *****************************************************
 @brief Backlight, library functions for EA LED36x28-ERW
 @file backlight.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for EA LED36x28-ERW backlight
 *****************************************************
 */

#include "backlight.h"

/*
@brief backlight_set_color, sets the color of the backlight White/Green/Red
@param const char *, pointer to char array.
@return void, no return value
*/
void backlight_set_color(const char *col) {

	if(strcmp(col, "Green") == 0 || strcmp(col, "green") == 0) {
		HAL_GPIO_WritePin(Disp_Green_GPIO_Port, Disp_Green_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Disp_Red_GPIO_Port, Disp_Red_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Disp_White_GPIO_Port, Disp_White_Pin, GPIO_PIN_RESET);
	} else if(strcmp(col, "Red") == 0 || strcmp(col, "red") == 0){
		backlight_set_brightness();
		HAL_GPIO_WritePin(Disp_Green_GPIO_Port, Disp_Green_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Disp_White_GPIO_Port, Disp_White_Pin, GPIO_PIN_RESET);
	} else if(strcmp(col, "White") == 0 || strcmp(col, "white") == 0) {
		HAL_GPIO_WritePin(Disp_White_GPIO_Port, Disp_White_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Disp_Red_GPIO_Port, Disp_Red_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Disp_Green_GPIO_Port, Disp_Green_Pin, GPIO_PIN_RESET);
	} else {
		Error_Handler();
	}
}

/*
@brief backlight_set_brightness, sets the brightness of the back light (Red only)
@param void, no parameter
@return void, no return value
*/
void backlight_set_brightness() {
	uint32_t adc_val = adc_get_value();
	htim3.Instance->CCR2 = adc_val;
}
