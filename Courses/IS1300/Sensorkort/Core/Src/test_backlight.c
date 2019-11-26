#include "test_backlight.h"

char green[] = "Green";
char red[] = "Red";
char white[] = "White";

void test_set_color() {
	set_color(red);
	HAL_Delay(1000);
	set_color(white);
	HAL_Delay(1000);
	set_color(green);
	HAL_Delay(1000);
}
