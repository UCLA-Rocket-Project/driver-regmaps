#pragma once
#include "register.h"
#include "bus.h"
#include "bitstuff.h"
#include <memory>
#include <cstdint>
#include "endianfix.h"
#include <tuple>

namespace regmap {
	using endianfix::endian;
	using endianfix::fixEndianess;
	using dev_addr_t = uint16_t;
	/**
	 * An implementation of a register map.
	 *
	 * @tparam WORD_SZ the type of each word in the regmap
	 * @tparam ENDIAN the endianness of the device
	 * @tparam REGS registers to memoize. Make sure that there are no duplicates in this register!
	 */
	template<endian ENDIAN,
		typename... MEMOIZED>
	class Regmap {
	public:
		static constexpr unsigned int NUM_MEMOIZED = sizeof...(MEMOIZED);
		std::tuple<RegType<MEMOIZED>...> memoizedRegs;
		bitset<NUM_MEMOIZED> seen = {0};
		dev_addr_t devAddr;
		std::shared_ptr<Bus> bus;

		Regmap(std::shared_ptr<Bus> bus, dev_addr_t addr): bus(std::move(bus)), devAddr(addr) {}

	private:
		// to reduce binary size, we'll template this only on the size of the register
		template<typename REG_SZ>
		int read(reg_addr_t regAddr, REG_SZ& dest) {
			return 69;
		}
	};
}