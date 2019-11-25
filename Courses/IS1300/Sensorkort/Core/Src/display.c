#include "display.h"

#define BUFFERSIZE 24
#define DISP_PKG_LENGTH 3 // No of bytes in one package to Display

uint32_t Buffer[] = {0xF84020};

uint32_t func_set = 0xF83010;
uint32_t clear_disp = 0xF80010;
uint32_t OSC_freq = 0xF81030;
uint32_t contrast = 0xF870F0;
uint32_t power_icon = 0xF850C0;
uint32_t follower_ctrl = 0xF860E0;
uint32_t power_on = 0xF800F0;



void init_display() {
	HAL_SPI_Transmit(&hspi2, (uint32_t *)func_set, BUFFERSIZE, 1000);
	HAL_SPI_Transmit(&hspi2, (uint32_t *)clear_disp, BUFFERSIZE, 1000);
	HAL_SPI_Transmit(&hspi2, (uint32_t *)OSC_freq, BUFFERSIZE, 1000);
	HAL_SPI_Transmit(&hspi2, (uint32_t *)contrast, BUFFERSIZE, 1000);
	HAL_SPI_Transmit(&hspi2, (uint32_t *)power_icon, BUFFERSIZE, 1000);
	HAL_SPI_Transmit(&hspi2, (uint32_t *)power_on, BUFFERSIZE, 1000);
}

void write_to_disp() {

}
