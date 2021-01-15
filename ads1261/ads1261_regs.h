#pragma once

#include <regmap/regmap.h>
namespace ads1261 {
	// control commands
	DECLR_CMD(NOP, 0x000)
	DECLR_CMD(RESET, 0x0600)
	DECLR_CMD(START, 0x0800)
	DECLR_CMD(STOP, 0x0A00)
	DECLR_REG(READ_CONV_CMD, 0x1200, uint32_t)
	DECLR_MASK(READ_CONV_STATUS, READ_CONV_CMD, 31, 24)
	DECLR_MASK(READ_CONV_DATA, READ_CONV_CMD, 23, 0)
	DECLR_CMD(LOCK, 0xF200)
	DECLR_CMD(UNLOCK, 0xF500)

	// config registers. Each address is added to 0x20
	enum ConfigRegisterAddrs: uint8_t {
		ID,
		STATUS,
		MODE0,
		MODE1,
		MODE2,
		MODE3,
		REF,
		OFCAL0,
		OFCAL1,
		OFCAL2,
		FSCAL0,
		FSCAL1,
		FSCAL2,
		IMUX,
		IMAG,
		RESERVED_DONT_USE,
		PGA,
		INPMUX,
		INPBIAS
	};
	template<ConfigRegisterAddrs CONFIG_REG_ADDR>
	using CfgReg = regmap::Reg<static_cast<uint8_t>(CONFIG_REG_ADDR) + 0x20, uint8_t>;


}