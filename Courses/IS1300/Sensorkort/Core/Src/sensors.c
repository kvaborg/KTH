/**
 *****************************************************
 @brief Backlight, library functions for sensors
 @file sensors.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for sensors LIS3DSH and HTS221
 *****************************************************
 */

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

typedef struct {

	/* Device Adress */
	uint8_t DEV_ADDR;

	/* Config register*/
	uint8_t CTRL_REG_6;
	uint8_t CTRL_REG_4;

	/* Value Register */
	uint8_t OUT_XYZ;
	uint8_t STATUS;

	/* Values */
	int16_t out_X;
	int16_t out_Y;
	int16_t out_Z;

}LIS3DSH_TypeDef;

LIS3DSH_TypeDef lis3dsh;
HTS221_TypeDef hts221;

/*
@brief hts_init, inits the HTS221_TypeDef struct by assingning register adresses.
@param void, no parameter.
@return void, no return value.
 */
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

/*
@brief hts_get_calib, gets the necessary calibration values before first temp and hum calculations.
@param void, no parameter.
@return void, no return value
 */
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
	config[1] = 0x85;

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

/*
@brief hts_get_hum_temp, gets temp and hum values from H_OUT and T_OUT and calculates the current temp and hum using linear interpolation.
@param void, no return value
@return uint8_t *, pointer to string with values for current temp and hum.
 */
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
		strcpy((char *)ret_buf, "Err Tx \r\n");
	} else {
		ret = HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, val, 4, HAL_MAX_DELAY);
		if (ret != HAL_OK) {
			strcpy((char *)ret_buf, "Err Rx \r\n");
		} else {

			// Convert and interpolate the temperature data
			t_out = (val[3] << 8) | val[2];
			temp = (hts221.T0_degC + ((t_out - hts221.T0_out) * (hts221.T1_degC - hts221.T0_degC)) / (hts221.T1_out - hts221.T0_out));

			// Convert and interpolate the humidity data
			h_out = (val[1] << 8) | val[0];
			hum = (hts221.H0_rh + ((h_out - hts221.H0_out) * (hts221.H1_rh - hts221.H0_rh)) / (hts221.H1_out - hts221.H0_out));

			sprintf((char *)ret_buf, "T=%02i H=%02i", (int)temp, (int)hum);
		}
	}

	usb_send_data((char *)ret_buf);
	return ret_buf;
}

/*
@brief lis3_init, inits the LIS3DSH_TypeDef struct by assigning register addresses.
@param void, no return value.
@return void, no return value.
 */
void lis3_init(void) {
	lis3dsh.DEV_ADDR = 0x1E << 1;
	lis3dsh.CTRL_REG_4 = 0x20;
	lis3dsh.CTRL_REG_6 = 0x25;
	lis3dsh.STATUS = 0x27;

	/* Value Register */
	lis3dsh.OUT_XYZ = 0x28;
}

/*
@brief lis3_get_xyz, gets values from OUT_X, OUT_Y and OUT_Z registers in order to calculate angles.
@param void, no return value.
@return void, no return value.
 */
volatile void lis3_get_xyz(void) {
	HAL_StatusTypeDef ret;
	uint8_t config[4];
	uint8_t reg[1];
	uint8_t data[] = {0,0,0,0,0,0};

	config[0] = lis3dsh.CTRL_REG_4;
	config[1] = 0x1F; // 1600 Hz and BDU = 1
	config[2] = lis3dsh.CTRL_REG_6;
	config[3] = 0x10; // Auto increment on

	ret = HAL_I2C_Master_Transmit(&hi2c3, lis3dsh.DEV_ADDR, config, 4, HAL_MAX_DELAY);
	HAL_Delay(10);

	if(ret != HAL_OK) {
		usb_send_data("lis3 Tx Error");
	} else {
		reg[0] = lis3dsh.STATUS;
		ret = HAL_I2C_Master_Transmit(&hi2c3, lis3dsh.DEV_ADDR, reg, 1, HAL_MAX_DELAY);

		if(ret != HAL_OK) {
			usb_send_data("lis3 Tx Error");
		} else {

			reg[0] = lis3dsh.OUT_XYZ;
			ret = HAL_I2C_Master_Transmit(&hi2c3, lis3dsh.DEV_ADDR, reg, 1, HAL_MAX_DELAY);

			if(ret != HAL_OK) {
				usb_send_data("lis3 Tx Error");
			} else {
				HAL_I2C_Master_Receive(&hi2c3, lis3dsh.DEV_ADDR, data, 6, HAL_MAX_DELAY);

				lis3dsh.out_X = (data[1] << 8) | data[0];
				lis3dsh.out_Y = (data[3] << 8) | data[2];
				lis3dsh.out_Z = (data[5] << 8) | data[4];
			}
		}
	}
}

/*
@brief lis3_calc_angle, calculates X and X angles from Z based on lis3_get_xyz values.
@param void, no return value.
@return uint8_t *, pointer to char array containing the angles for X and Y relative to Z.
 */
uint8_t * lis3_calc_angle() {
	double angle_x_rad, angle_y_rad;
	int8_t angle_x, angle_y;
	static uint8_t ret_buf[10];

	angle_x_rad = atan(lis3dsh.out_X / (sqrt(pow(lis3dsh.out_Y, 2) + pow(lis3dsh.out_Z, 2))));
	angle_y_rad = atan(lis3dsh.out_Y / (sqrt(pow(lis3dsh.out_X, 2) + pow(lis3dsh.out_Z, 2))));

	angle_x = 90 - (uint8_t)fabs(angle_x_rad * 180.0 / M_PI);
	angle_y = 90 - (uint8_t)fabs(angle_y_rad * 180.0 / M_PI);

	sprintf((char *)ret_buf, "X=%02u Y=%02u", (unsigned int)angle_x, (unsigned int)angle_y);

	return ret_buf;
}
