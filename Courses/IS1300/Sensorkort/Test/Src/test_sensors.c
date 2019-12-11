#include "../Inc/test_sensors.h"

void test_hts_get_hum_temp(void) {
	hts_init();
	hts_get_calib();
	while(1) {
		hts_get_hum_temp();
	}
}

void test_lis3_get_xyz(void) {
	lis3_init();

	while(1) {
		lis3_get_xyz();
		lis3_calc_angle();
	}
}
