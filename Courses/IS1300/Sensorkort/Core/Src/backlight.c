#include "backlight.h"

void set_color(char *col) {

	if(strcmp(col, "Green") == 0 || strcmp(col, "green") == 0) {
		HAL_GPIO_WritePin(Disp_Green_GPIO_Port, Disp_Green_Pin, SET);
	} else if(strcmp(col, "Red") == 0 || strcmp(col, "red") == 0){
		HAL_GPIO_WritePin(Disp_Red_GPIO_Port, Disp_Red_Pin, SET);
	} else if(strcmp(col, "White") == 0 || strcmp(col, "white") == 0) {
		HAL_GPIO_WritePin(Disp_White_GPIO_Port, Disp_White_Pin, SET);
	} else {

	}

}
