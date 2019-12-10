#include "../Inc/test_sensors.h"

void test_hts_get_hum_temp(void) {
	hts_init();
	hts_get_calib();
	while(1) {
		hts_get_hum_temp();
	}
}
