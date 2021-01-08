#pragma once
#ifndef ADXL375_REGMAP_H
#define ADXL375_REGMAP_H
#include <stdint.h>
#include <regmap/regmap.h>

REG_BYTE(DEVICE_ID, 0)
REG_BYTE(THRESH_SHOCK, 0x1D)
REG_BYTE(OFSX, 0x1E)
REG_BYTE(OFSY, 0x1F)
REG_BYTE(OFSZ, 0x20)
REG_BYTE(DUR, 0x21)
REG_BYTE(LATENT, 0x22)
REG_BYTE(WINDOW, 0x23)
REG_BYTE(THRESH_ACT, 0x24)
REG_BYTE(THRESH_INACT, 0x25)
REG_BYTE(TIME_INACT, 0x26)
REG_BYTE(ACT_INACT_CTL, 0x27)
REG_BYTE(SHOCK_AXES, 0x2A)
REG_BYTE(ACT_SHOCK_STATUS, 0x43)
REG_BYTE(BW_RATE, 0x2C)
REG_BYTE(POWER_CTL, 0x2D)
REG_BYTE(INT_EN, 0x2E)
REG_BYTE(INT_MAP, 0x2F)
REG_BYTE(INT_SRC, 0x30)
REG_BYTE(DATA_FMT, 0x31)
REG_BYTE(DATAX0, 0x32)
REG_BYTE(DATAX1, 0x33)
REG_BYTE(DATAY0, 0x34)
REG_BYTE(DATAY1, 0x35)
REG_BYTE(DATAZ0, 0x36)
REG_BYTE(DATAZ1, 0x37)
REG_BYTE(FIFO_CTL, 0x38)
REG_BYTE(FIFO_STATUS, 0x39)

#endif