#pragma once
#ifndef MS5611_LOWLEVEL_H
#define MS5611_LOWLEVEL_H
#include <stdint.h>
#include "regmap/regmap.h"

// I2C / SPI commands
#define MS5611_CMD_RESET 0x1E
#define MS5611_CMD_D1 0x40
#define MS5611_CMD_D2 0x50
#define MS5611_CMD_ADC_READ 0x00
#define MS5611_CMD_PROM_READ 0xA0

enum ms5611_prom_field {
	MS5611_PROM_FACTORY,
	MS5611_PROM_SENSt1,
	MS5611_PROM_OFFt1,
	MS5611_PROM_TCS,
	MS5611_PROM_TCO,
	MS5611_PROM_Tref,
	MS5611_PROM_TEMPSENS,
	MS5611_PROM_CRC
};
enum ms5611_osr_rate {
	MS5611_OSR_256,
	MS5611_OSR_512,
	MS5611_OSR_1024,
	MS5611_OSR_2048,
	MS5611_OSR_4096
};
/**
 * Resets a device
 */
int ms5611_reset(struct reg_bus* dev);
/**
 * Reads in a PROM field
 */
int ms5611_read_prom(enum ms5611_prom_field field, uint16_t* val, struct reg_bus *dev);
/**
 * Starts a pressure conversion
 */
int ms5611_start_press_conv(enum ms5611_osr_rate osrRate, struct reg_bus* dev);
/**
 * Starts a temperature conversion
 */
int ms5611_start_temp_conv(enum ms5611_osr_rate osrRate, struct reg_bus* dev);
/**
 * Reads back the conversion result
 * @param val The pointer to hold the result. NOTE: this is 24-bits only.
 */
int ms5611_read_conv(uint32_t *val, struct reg_bus* dev);

#endif