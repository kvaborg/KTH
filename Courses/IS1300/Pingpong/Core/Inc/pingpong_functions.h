#ifndef PINGPONG_FUNCTIONS_H
#define PINGPONG_FUNCTIONS_H
#endif

#include "stdint.h"
#include "stdbool.h"
#include "gpio.h"

void Led_on(uint8_t Lednr);
void Blink_LEDs(uint8_t times);
void Show_points(uint8_t L_points, uint8_t R_points, uint32_t duration);
bool L_hit(void);
bool R_hit(void);
