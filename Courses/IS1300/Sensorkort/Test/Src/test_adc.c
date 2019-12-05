#include "../Inc/test_adc.h"

void test_adc_get_value() {
	int i;
	char adc_str[10];

	for(i = 0; i < 10; i++) {
		int val = adc_get_value();
		sprintf(adc_str, "%d", val);
		usb_send_data(adc_str);
		HAL_Delay(1000);
	}
}
