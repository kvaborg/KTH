#include "test.h"
#include "gpio.h"
#include "pingpong.h"

void Test_program(void)
{
	Test_Led();
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
