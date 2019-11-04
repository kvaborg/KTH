/**
 *****************************************************
 @brief Pingpong, functions for Pingpong-program
 @file pingpong_functions.c
 @author Alexander Borg
 @version 1.0
 @date 4-November-2019
 @brief Functions and structures for program Pingpong
 *****************************************************
 */

#include "gpio.h"
#include "pingpong_functions.h"

/**
@brief Led_on, turn one of the pingpong leds on
@param uint8_t Lednr, number to the Led that is turned on
 	   Lednr can be 1-8, all other values turns all leds off.
@return void
*/
void Led_on(uint8_t Lednr)
{
	const uint32_t PORTS[] = {LED_1_GPIO_Port, LED_2_GPIO_Port, LED_3_GPIO_Port, LED_4_GPIO_Port, LED_5_GPIO_Port,
						LED_6_GPIO_Port, LED_7_GPIO_Port, LED_8_GPIO_Port};
	const uint16_t PINS[] = {LED_1_Pin, LED_2_Pin, LED_3_Pin, LED_4_Pin, LED_5_Pin, LED_6_Pin,
						LED_7_Pin, LED_8_Pin};

	uint8_t i;
	for (i=1; i<=8; i++)
	{
		if (Lednr==i) HAL_GPIO_WritePin(PORTS[i-1], PINS[i-1], GPIO_PIN_SET);
		else HAL_GPIO_WritePin(PORTS[i-1], PINS[i-1], GPIO_PIN_RESET);
	} // End for loop
	return;
} // End of function Led_on

/*
@brief Show_points, shows points after missed ball
@param1 uint8_t L_points points for left player
@param2 uint8_t R_points points for right player
@return void, no return value
*/
void Show_points(uint8_t L_points, uint8_t R_points)
{
	const uint32_t L_PORTS[] = {LED_1_GPIO_Port, LED_2_GPIO_Port, LED_3_GPIO_Port, LED_4_GPIO_Port};
	const uint16_t L_PINS[] = {LED_1_Pin, LED_2_Pin, LED_3_Pin, LED_4_Pin};

	const uint32_t R_PORTS[] = {LED_8_GPIO_Port, LED_7_GPIO_Port, LED_6_GPIO_Port, LED_5_GPIO_Port};
	const uint16_t R_PINS[] = {LED_8_Pin, LED_7_Pin, LED_6_Pin, LED_5_Pin};

	uint8_t i;

	// Blink 0.1 s after missed ball
	for (i=0; i<4; i++)
	{
		HAL_GPIO_WritePin(R_PORTS[i], R_PINS[i], GPIO_PIN_SET);
		HAL_GPIO_WritePin(L_PORTS[i], L_PINS[i], GPIO_PIN_SET);
	}

	HAL_Delay(100);

	for (i=0; i<4; i++)
		{
			HAL_GPIO_WritePin(R_PORTS[i], R_PINS[i], GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L_PORTS[i], L_PINS[i], GPIO_PIN_RESET);
		}

	HAL_Delay(500);

	// Right points
	for (i=0; i<R_points; i++)
		HAL_GPIO_WritePin(R_PORTS[i], R_PINS[i], GPIO_PIN_SET);

	// Left points
	for (i=0; i<L_points; i++)
		HAL_GPIO_WritePin(L_PORTS[i], L_PINS[i], GPIO_PIN_SET);

	HAL_Delay(1000);

	// Reset all pins
	for (i=0; i<4; i++)
	{
		HAL_GPIO_WritePin(R_PORTS[i], R_PINS[i], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(L_PORTS[i], L_PINS[i], GPIO_PIN_RESET);
	}
}
