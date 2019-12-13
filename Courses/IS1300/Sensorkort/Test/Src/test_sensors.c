/**
 *****************************************************
 @brief Test Sensors, Tests for sensor functions
 @file test.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for sensor function tests.
 *****************************************************
 */
#include "../Inc/test_sensors.h"

/*
@brief test_hts_get_hum_temp, tests the hts_get_hum_temp fucntion
@param void, no parameters
@return void, no return value
 */
void test_hts_get_hum_temp(void) {
	hts_init();
	hts_get_calib();
	while(1) {
		hts_get_hum_temp();
	}
}

/*
@brief test_lis3_calc_angle, tests the lis3_calc_angle fucntion
@param void, no parameters
@return void, no return value
 */
void test_lis3_calc_angle(void) {
	lis3_init();

	while(1) {
		lis3_get_xyz();
		lis3_calc_angle();
	}
}
