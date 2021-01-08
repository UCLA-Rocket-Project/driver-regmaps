#pragma once
#include <cstdint>

namespace regmap {
	/**
	 * Generates a bitmask like Verilog bits[h:l] where 0
	 * represents the selected bits
	 * BITMASK(3, 1) = 0b00001110
	 */
	template <typename WORD_SZ>
	constexpr inline WORD_SZ static_bitmask(uint8_t highBit, uint8_t lowBit) {
		return ~(~0 << (highBit - lowBit + 1)) << lowBit;
	}
	/**
	 * We move as many values as possible in order to reduce the memory used
	 * after compilation. Expected overhead is:
	 * register size (T_HIGH_BIT - T_LOW_BIT + 1) + 1 bit for whether the value is known,
	 * rounded to the nearest byte
	 *
	 * @tparam ADDR_SZ The size of each register address
	 * @tparam WORD_SZ The size of the value addressed by each register
	 * @tparam T_REG_ADDR The address of the register
	 * @tparam T_HIGH_BIT The high-bit of the register
	 * @tparam T_LOW_BIT The low-bit of the register
	 */
	template <typename ADDR_SZ, typename WORD_SZ,
		ADDR_SZ T_REG_ADDR, uint8_t T_HIGH_BIT, uint8_t T_LOW_BIT>
	struct Register {
		static constexpr ADDR_SZ REG_ADDR = T_REG_ADDR;
		static constexpr uint8_t HIGH_BIT = T_HIGH_BIT;
		static constexpr uint8_t LOW_BIT = T_LOW_BIT;
		static constexpr WORD_SZ MASK = static_bitmask<WORD_SZ>(T_HIGH_BIT, T_LOW_BIT);
	};
	/**
	 * Convinence definition for devices which with 255x255 registers.
	 */
	template <uint8_t REGISTER, uint8_t HIGH_BIT, uint8_t LOW_BIT>
	using ByteRegister = Register<uint8_t, uint8_t, REGISTER, HIGH_BIT, LOW_BIT>;

	using WHOAMI = ByteRegister<0x30, 6, 4>;
}

