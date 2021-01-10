#pragma once
#include <cstdint>
#include <utility>
#include <initializer_list>
#include <algorithm>
#include "bitstuff.h"
#include "endianfix.h"

namespace regmap {
	using reg_addr_t = uint16_t;
	using endianfix::uint24_t;

	template<reg_addr_t reg_addr, typename reg_size>
	struct Register {
		static_assert(
			std::is_integral<reg_size>::value,
			// || std::is_same<reg_size, uint24_t>::value, deal with dumb 24bit stuff later
			"Registers must be backed by integer values");
		static constexpr reg_addr_t addr = reg_addr;
		using backingType = reg_size;
	};
	template<typename REG>
	constexpr reg_addr_t addr() {
		return REG::addr;
	}
	template<typename REG>
	using BackingType = typename REG::backingType;

	template<typename REG, uint8_t mask_high, uint8_t mask_low>
	struct RegMask {
		using backingReg = REG;
		static constexpr uint8_t maskHigh = mask_high;
		static constexpr uint8_t maskLow = mask_low;
	};
	template<typename MASK>
	constexpr typename MASK::backingReg::backingType bitmask() {
		using WORD_SZ = typename MASK::backingReg::backingType;
		WORD_SZ i = WORD_SZ(); // a safe way to initialize the variable to 0
		i = ~i; // now flip all the bits before we mask
		return ~( (WORD_SZ)i << MASK::maskHigh << 1) & (i << MASK::maskLow);
	}
	template<typename MASK>
	constexpr typename MASK::backingReg::backingType shiftInValue(typename MASK::backingReg::backingType value) {
		return (value << MASK::maskLow) & bitmask<MASK>();
	}
	template<typename MASK>
	constexpr typename MASK::backingReg::backingType shiftOutValue(typename MASK::backingReg::backingType value) {
		return (value & bitmask<MASK>()) >> MASK::maskLow;
	}
}

#define REG(NAME, ADDR, HIGHBIT, LOWBIT) constexpr regmap::Register NAME = regmap::newRegister(ADDR, HIGHBIT, LOWBIT);
#define REG_BYTE(NAME, ADDR) constexpr regmap::Register NAME = regmap::newRegister(ADDR, 7, 0);