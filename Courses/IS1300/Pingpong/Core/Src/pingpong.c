/**
 *****************************************************
 @brief Pingpong, Pingpong-program
 @file pingpong.c
 @author Alexander Borg
 @version 1.0
 @date 4-November-2019
 @brief Source code for program Pingpong
 *****************************************************
 */

#include "pingpong.h"

typedef enum
{  Start,
	MoveRight,
	MoveLeft,
	ShowScore
} states;

static states State, NextState;

/*
@brief Pingpong, state machine game function.
@param void, no parameters
@return void, no return value
*/
void Pingpong(void)
{
	bool ButtonPressed = false; // To remember that button is pressed
	bool R_serve, L_serve;

	uint32_t Varv, Speed; // Ball speed
	uint8_t Led; // LEDnr
	uint8_t L_points, R_points;

	State=Start; // Initiate State to Start
	NextState=Start;
	L_points = 0;
	R_points = 0;
	L_serve = true;
	R_serve = true;

	// Number of loops
	/* Infinite loop */
	while (L_points < 4 && R_points < 4)
	{
		State = NextState;
		switch (State) // State machine
		{
		case Start :
		{
			Speed = 500000;
			Led_on(0); // Turn off all LEDs
			if (L_hit() == true && L_serve == true) // L serve
			{
				L_serve = false;
				R_serve = true;
				Led = 1;
				NextState=MoveRight;
				while (L_hit() == true); // wait until button is released
			}
			else
			{
				if (R_hit() == true && R_serve == true) // R serve
				{
					L_serve = true;
					R_serve = false;
					Led = 8;
					NextState=MoveLeft;
					while (R_hit() == true); // wait until button is released
				}
				else
					NextState = Start; //Stay in Start state
			}
		}
		break;

		case MoveRight :
		{
			Led_on(Led);
			Varv = Speed;

			while (Varv != 0)
			{
				if (R_hit()) ButtonPressed = true; // R hit
				Varv--;
			}
			if (ButtonPressed) // R pressed
			{
				if (Led == 8) // and LED8 active
				{
					Speed -= 50000;
					NextState=MoveLeft; // return ball
					Led=7;
				}
				else
				{
					L_points++;
					NextState=ShowScore; // hit to early
				}
			}
			else
			{
				if (Led == 9) // no hit or to late
				{
					L_points++;
					NextState=ShowScore;
				}
				else
					NextState=MoveRight; // ball continues to move right
			}
			if (!ButtonPressed) Led++; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;

		case MoveLeft :
		{
			Led_on(Led);
			Varv = Speed;
			while (Varv != 0)
			{
				if (L_hit()) ButtonPressed = true; // L hit
				Varv--;
			}
			if (ButtonPressed) // L pressed
			{
				if (Led == 1)	// and LED1 active
				{
					Speed -= 50000;
					NextState=MoveRight; // return ball
					Led=2;
				}
				else
				{
					R_points++;
					NextState=ShowScore; // hit to early
				}
			}
			else
			{
				if (Led == 0) // no hit or to late
				{
					R_points++;
					NextState=ShowScore;
				}
				else
					NextState=MoveLeft; // ball continues to move left
			}
			if (!ButtonPressed) Led--; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;

		case ShowScore :
		{
			Show_points(L_points, R_points, 1000);
			NextState=Start;
			break;
		}

		default :
			break;
		}
	}
	Show_points(L_points, R_points, 5000);
} // End of function Pingpong

