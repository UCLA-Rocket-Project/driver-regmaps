#pragma once
#include "register.h"
#include "bus.h"
namespace regmap {
	template <typename ADDR_SZ, typename WORD_SZ,
		ADDR_SZ REG_ADDR, uint8_t HIGH_BIT, uint8_t LOW_BIT>
	inline int writeRegister(Bus* bus, Register<ADDR_SZ, WORD_SZ, REG_ADDR, HIGH_BIT, LOW_BIT>* reg) {
		reg->REG_ADDR = 4;
	}
}