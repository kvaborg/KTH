/**
 *****************************************************
 @brief Tests, tests for Pingpong-fuctions
 @file tests.c
 @author Alexander Borg
 @version 1.0
 @date 4-November-2019
 @brief Tests for all pingpong_functions.c functions
 *****************************************************
 */

#include "test.h"

/**
@brief Test_program, Entry point for running tests
@param void, no parameters
@return void, no return value
*/
void Test_program(void)
{
	//Test_Led();
	//Test_Blink_LEDs();
	Test_Show_points();
	//Test_buttons();
}

/**
@brief Test_Led, tests all leds by turning them on and off
@param void, no parameters
@return void, no return value
*/
void Test_Led(void)
{
	int8_t Lednr;
	/* Loop checking that all leds can be turned on */
	for (Lednr=1; Lednr<=8; Lednr++)
	{
		Led_on(Lednr);
		HAL_Delay(500);
	}
	Led_on(9); // Turn off led 8
	HAL_Delay(1000); // 1000 ms
}

void Test_Blink_LEDs(void)
{
	Blink_LEDs(5);
}

/**
@brief Test_Show_points, tests leds for showing points when scoring a goal
@param void, no parameters
@return void, no return value
*/
void Test_Show_points(void)
{
	uint8_t L_point, R_point;
	for(L_point=0; L_point<=4; L_point++)
	{
		for(R_point=0; R_point<=4; R_point++)
		{
			Show_points(L_point, R_point, 1000);
			HAL_Delay(500);
		}
	}
}

/**
@brief Test_buttons, tests if R and L button is pressed
@param void, no parameters
@return void, no return value
*/
void Test_buttons(void)
{
	int8_t j;

	/* Checking buttons */

	j=4;
	Led_on(j); // Light on

	while(j<9 && j>0)
	{
		if (L_hit() == true) // Wait for left button hit
		{
			j++;	// Next led to the right
			Led_on(j);	// Light on
			HAL_Delay(100);	// 100 ms
			while(L_hit() == true);	// Wait for button release
			HAL_Delay(100);	// 100 ms
		}

		if (R_hit() == true) // Wait for right button hit
		{
			j--;	// Next led to the left
			Led_on(j);	// Light on
			HAL_Delay(100);	// 100 ms
			while(R_hit() == true);	// Wait for button release
			HAL_Delay(100);	// 100 ms
			if(j<1) j=0; // Start again from left
		}
	}
	return;
}
