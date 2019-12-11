/**
 *****************************************************
 @brief Sensorkort, Sensorkort-program
 @file sensorkort.c
 @author Alexander Borg
 @version 1.0
 @date 12-December-2019
 @brief Source code for sensorkort-program
 *****************************************************
 */

#include "sensorkort.h"

void sensorkort() {
	lcd_init();
	rtc_set_time();
	hts_init();
	hts_get_calib();
	lis3_init();

	while(1) {
		backlight_set_brightness();
		lis3_get_xyz();
		display_all();
	}
}
