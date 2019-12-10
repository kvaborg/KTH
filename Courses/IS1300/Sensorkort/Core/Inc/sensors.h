#ifndef HTS_H
#define HTS_H
#endif

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "i2c.h"

void hts_init(void);
void hts_get_calib(void);
uint8_t * hts_get_hum_temp(void);




