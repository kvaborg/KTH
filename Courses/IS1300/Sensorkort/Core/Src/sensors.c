#include <sensors.h>

typedef struct  {

	/* HTS221 Registers */
	uint16_t DevAddr;
	uint8_t HTS_REG_HUM_TEMP; // Read 4 bytes, hum msb, hum lsb, temp msb, temp lsb. Auto increment set.
	uint8_t HTS_REG_TEMP;
	uint8_t H0_rH_x2;
	uint8_t H1_rH_x2;
	uint8_t T0_degC_x8;
	uint8_t T1_degC_x8;
	uint8_t T1_T0_msb;
	uint8_t H0_T0_OUT;
	uint8_t H1_T0_OUT;
	uint8_t T0_OUT;
	uint8_t T1_OUT;

	/*HTS221 Calibration values*/
	int16_t H0_rh;
	int16_t H1_rh;
	int16_t H0_out;
	int16_t H1_out;

	int16_t T0_degC;
	int16_t T1_degC;
	int16_t T0_out;
	int16_t T1_out;

} HTS221_TypeDef;

HTS221_TypeDef hts221;

void hts_init() {
	hts221.DevAddr = 0x5F << 1;
	hts221.HTS_REG_HUM_TEMP = 0xA8; // Read 4 bytes, hum msb, hum lsb, temp msb, temp lsb. Auto increment set.
	hts221.H0_rH_x2 = 0x30;
	hts221.H1_rH_x2 = 0x31;
	hts221.T0_degC_x8 = 0x32;
	hts221.T1_degC_x8 = 0x33;
	hts221.T1_T0_msb = 0x35;
	hts221.H0_T0_OUT = 0xB6; // Read 2 bytes msb, ls. Auto increment set.
	hts221.H1_T0_OUT = 0xBA; // Read 2 bytes msb, ls. Auto increment set.
	hts221.T0_OUT = 0xBC; // Read 2 bytes msb, ls. Auto increment set.
	hts221.T1_OUT = 0xBE; // Read 2 bytes msb, ls. Auto increment set.
}

volatile void hts_get_calib() {
	uint8_t reg[1];
	uint8_t data[4];
	uint8_t config[2] = {0};

	//	config[0] = 0x10;
	//	config[1] = 0x1B;
	//
	//	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, config, 2, HAL_MAX_DELAY);
	//	HAL_Delay(100);

	config[0] = 0x20;
	config[1] = 0x87;

	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, config, 2, HAL_MAX_DELAY);
	HAL_Delay(100);


	/*
	 * Humidity Calibration values
	 */

	/* Read H0_rH_x2 register*/
	reg[0] = hts221.H0_rH_x2;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY); // Init read from slave
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 1, HAL_MAX_DELAY);
	int data_0 = data[0];

	/* Read H1_rH_x2 register*/
	reg[0] = hts221.H1_rH_x2;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY); // Init read from slave
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 1, HAL_MAX_DELAY);
	int data_1 = data[0];

	hts221.H0_rh = data_0 >> 1;
	hts221.H1_rh = data_1 >> 1;

	/* Read H0_T0_OUT register*/
	reg[0] = hts221.H0_T0_OUT;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY); // Read 2 bytes
	data_0 = data[0];
	data_1 = data[1];

	hts221.H0_out = (data_1 << 8) | data_0;

	/* Read H1_T0_OUT register*/
	reg[0] = hts221.H1_T0_OUT;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY); // Read 2 bytes
	data_0 = data[0];
	data_1 = data[1];

	hts221.H1_out = (data_1 << 8) | data_0;

	/*
	 * Temperature Calibration values
	 */

	/* Read T1_T0_msb register*/
	reg[0] = hts221.T1_T0_msb;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 1, HAL_MAX_DELAY);

	int raw = data[0];

	/* Read T0_degC_x8 register*/
	reg[0] = hts221.T0_degC_x8;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 1, HAL_MAX_DELAY);
	hts221.T0_degC = data[0];

	hts221.T0_degC = (hts221.T0_degC + (1 << 8) * (raw & 0x03)) >> 3;

	/* Read T1_degC_x8 register*/
	reg[0] = hts221.T1_degC_x8;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 1, HAL_MAX_DELAY);
	hts221.T1_degC = data[0];

	hts221.T1_degC = (hts221.T1_degC + (1 << 6) * (raw & 0x0C)) >> 3;

	/* Read T0_OUT register*/
	reg[0] = hts221.T0_OUT;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY); // Read 2 bytes
	data_0 = data[0];
	data_1 = data[1];

	hts221.T0_out = (data_1 << 8) | data_0;

	/* Read T1_OUT register*/
	reg[0] = hts221.T1_OUT;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY); // Read 2 bytes
	data_0 = data[0];
	data_1 = data[1];

	hts221.T1_out = (data_1 << 8) | data_0;
}


uint8_t * hts_get_hum_temp(void) {
	HAL_StatusTypeDef ret;

	uint8_t val[4];
	uint8_t reg[1];
	static uint8_t ret_buf[12];
	int16_t t_out, h_out;
	int16_t temp, hum;

	reg[0] = hts221.HTS_REG_HUM_TEMP;
	ret = HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);

	if(ret != HAL_OK) {
		strcpy((char *)ret_buf, "Error Tx \r\n");
	} else {
		ret = HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, val, 4, HAL_MAX_DELAY);
		if (ret != HAL_OK) {
			strcpy((char *)ret_buf, "Error Rx \r\n");
		} else {

			// Convert the temperature data
			t_out = (val[3] << 8) | val[2];
			temp = (hts221.T0_degC + ((t_out - hts221.T0_out) * (hts221.T1_degC - hts221.T0_degC)) / (hts221.T1_out - hts221.T0_out));

			// Convert the humidity data
			h_out = (val[1] << 8) | val[0];
			hum = (hts221.H0_rh + ((h_out - hts221.H0_out) * (hts221.H1_rh - hts221.H0_rh)) / (hts221.H1_out - hts221.H0_out));


			sprintf((char *)ret_buf, "TEMP = %02i HUM = %02i", (int)temp, (int)hum);
		}
	}

	usb_send_data((char *)ret_buf);
	return ret_buf;
}
