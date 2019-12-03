/**
 *****************************************************
 @brief Backlight, header file
 @file backlight.h
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Header file for EA LED36x28-ERW backlight
 *****************************************************
 */

#ifndef BACKLIGHT_H
#define BACKLIGHT_H
#endif

#include  "tim.h"
#include "adc.h"
#include "spi.h"
#include <stdbool.h>
#include <string.h>

void backlight_set_color(const char *);
void backlight_set_brightness(void);
