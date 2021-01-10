#pragma once
#include <cstdint>
#include <type_traits>
#include "bitstuff.h"
#include "endianfix.h"

namespace regmap {
	/* Register definitions */
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
	constexpr reg_addr_t RegAddr() {
		return REG::addr;
	}
	template<typename REG>
	using RegType = typename REG::backingType;

	/* Mask definitions */
	template<typename REG, uint8_t mask_high, uint8_t mask_low>
	struct RegMask {
		using backingReg = REG;
		static constexpr uint8_t maskHigh = mask_high;
		static constexpr uint8_t maskLow = mask_low;
	};
	template <typename MASK>
	using RegOf = typename MASK::backingReg;
	template <typename MASK>
	constexpr uint8_t MaskH() {
		return MASK::maskHigh;
	}
	template<typename MASK>
	constexpr uint8_t MaskL() {
		return MASK::maskLow;
	}
	template<typename MASK>
	using MaskType = RegType<RegOf<MASK>>;

	/* Bitmask utility */
	template<typename MASK>
	constexpr MaskType<MASK> bitmask() {
		using WORD_SZ = MaskType<MASK>;
		WORD_SZ i = WORD_SZ(); // a safe way to initialize the variable to 0
		i = ~i; // now flip all the bits before we mask
		return ~( (WORD_SZ)i << MASK::maskHigh << 1) & (i << MASK::maskLow);
	}
	/* Register mask utility to shift in and out mask values */
	template<typename MASK>
	constexpr MaskType<MASK> shiftInValue(MaskType<MASK> value) {
		return (value << MASK::maskLow) & bitmask<MASK>();
	}
	template<typename MASK>
	constexpr MaskType<MASK> shiftOutValue(MaskType<MASK> value) {
		return (value & bitmask<MASK>()) >> MASK::maskLow;
	}
	/* Register mask merging */
	// define min and max here
	template <typename MASK1, typename MASK2>
	constexpr uint8_t minLowBit() {
		return (MaskL<MASK1>() < MaskL<MASK2>()) ? MaskL<MASK1>() : MaskL<MASK2>();
	}
	template <typename MASK1, typename MASK2>
	constexpr uint8_t maxHighBit() {
		return (MaskH<MASK1>() > MaskH<MASK2>()) ? MaskH<MASK1>() : MaskH<MASK2>();
	}

	// the value version
	template <typename MASK1, typename MASK2>
	using SameReg = std::is_same<RegOf<MASK1>, RegOf<MASK2>>;
	template <typename MASK1, typename MASK2>
	constexpr MaskType<MASK1> merge2Masks(
		MaskType<MASK1> val1,
		MaskType<MASK1> val2) {

		static_assert(SameReg<MASK1, MASK2>::value,
			"Can only merge 2 masks of the same register");
		return shiftInValue<MASK1>(val1) | shiftInValue<MASK2>(val2);
	}
	// the type version
	template <typename MASK1, typename MASK2>
	using Merge2Masks = std::enable_if_t<SameReg<MASK1, MASK2>::value,
		RegMask<
		    RegOf<MASK1>,
	        maxHighBit<MASK1, MASK2>(),
            minLowBit<MASK1, MASK2>()
        >>;
	/* **begin chants to summon the god of meta-programming** */
	/*
	 * top-level: exists solely for the compiler
	 */
	// value version
	template <typename ...MASKS>
	constexpr unsigned int mergeMasks();
	// type version

	// base case: merge zero masks. In that case, return 0
	template <>
	constexpr unsigned int mergeMasks() {
		return 0;
	}
	// recursive case: mergeMasks(head, tail) => merge2Masks(head, mergeMasks(tail))
	template <typename HEAD, typename...TAIL>
	constexpr RegType<RegOf<HEAD>> mergeMasks(
		RegType<RegOf<HEAD>> headVal,
		RegType<RegOf<TAIL>>...tailVals) {

		auto tail = mergeMasks<TAIL...>(tailVals...);
		return mergeMasks<HEAD, decltype(tail)>(headVal, tailVals...);
	}
}

#define REG(NAME, ADDR, HIGHBIT, LOWBIT) constexpr regmap::Register NAME = regmap::newRegister(ADDR, HIGHBIT, LOWBIT);
#define REG_BYTE(NAME, ADDR) constexpr regmap::Register NAME = regmap::newRegister(ADDR, 7, 0);