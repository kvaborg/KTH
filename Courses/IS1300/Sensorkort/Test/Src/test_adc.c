#include "../Inc/test_adc.h"

void test_adc_get_value() {
	int i;

	for(i = 0; i < 10; i++) {
		uint32_t val = adc_get_value();
		usb_send_data(val);
		HAL_Delay(100);
	}
}
