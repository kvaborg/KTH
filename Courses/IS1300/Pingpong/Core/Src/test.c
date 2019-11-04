#include "test.h"
//#include "gpio.h"
//#include "pingpong_functions.h"

void Test_program(void)
{
	//Test_Led();
	Test_Show_points();
}

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

void Test_Show_points(void)
{
	uint8_t L_point, R_point;
	for(L_point=0; L_point<=4; L_point++)
	{
		for(R_point=0; R_point<=4; R_point++)
		{
			Show_points(L_point, R_point);
			HAL_Delay(500);
		}
	}
}
