#ifndef HTS_H
#define HTS_H
#endif

#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "i2c.h"

void hts_init(void);
volatile void hts_get_calib(void);
uint8_t * hts_get_hum_temp(void);
void lis3_init(void);
volatile void lis3_get_xyz(void);
uint8_t * lis3_calc_angle(void);




