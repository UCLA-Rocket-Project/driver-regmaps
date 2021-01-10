#pragma once
#include <cstdint>

#include <regmap/regmap.h>
using namespace regmap;

/* Define test registers */
using ZERO_REG = Register<0, uint8_t>;
using ONE_REG = Register<1, uint8_t>;
using WORD_REG = Register<0x10, uint16_t>;

/* Define test register masks */
using MID_NIBBLE = RegMask<ONE_REG, 5, 2>;
using WORD_BYTE_H = RegMask<WORD_REG, 15, 8>;
using WORD_BYTE_L = RegMask<WORD_REG, 7, 0>;