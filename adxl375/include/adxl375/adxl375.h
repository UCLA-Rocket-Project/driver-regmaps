#pragma once
#ifndef ADXL375_H
#define ADXL375_H
#include <stdint.h>
#include <regmap/register.h>

#define ADXL375_DEVID 0xE5
inline uint8_t ADXL375_SHOCK_THRESH_G(unsigned int g) {
	return (g * 1000) / 780;
}
inline uint8_t ADXL375_BANDWIDTH_HZ(unsigned int bw) {

}
#endif