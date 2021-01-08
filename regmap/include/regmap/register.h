#pragma once
#include <cstdint>
#include <utility>
#include <initializer_list>
#include "bitstuff.h"

namespace regmap {
	using Register = uint32_t;
	constexpr Register newRegister(uint16_t addr, uint8_t highBit, uint8_t lowBit) {
		return ( ( (uint32_t)addr ) << 16) + (highBit << 8) + lowBit;
	}
	constexpr uint16_t getAddr(Register r) {
		return r >> 16;
	}
	constexpr uint8_t getHighBit(Register r) {
		return (r >> 8) & 0xFF;
	}
	constexpr uint8_t getLowBit(Register r) {
		return r & 0xFF;
	}
	constexpr uint8_t getWidthBits(Register r) {
		return getHighBit(r) - getLowBit(r) + 1;
	}
	constexpr uint8_t getWidthBytes(Register r) {
		return requiredBytes(getWidthBits(r));
	}
	template <typename WORD_SZ>
	constexpr WORD_SZ getBitmask(Register r) {
		return bitmask<WORD_SZ>(getHighBit(r), getLowBit(r));
	}
}

#define REG(NAME, ADDR, HIGHBIT, LOWBIT) constexpr regmap::Register NAME = regmap::newRegister(ADDR, HIGHBIT, LOWBIT);
#define REG_BYTE(NAME, ADDR) constexpr regmap::Register NAME = regmap::newRegister(ADDR, 7, 0);