#pragma once
#include <cstdint>
#include <type_traits>
namespace regmap {
	// BITSET
	/**
	 * Get the required bytes needed to hold N bits
	 * @param n the number of bits to hold
	 * @return the number of bytes necessary
	 */
	constexpr unsigned int requiredBytes(unsigned int n) {
		return n % 8 == 0 ? n / 8 : n / 8 + 1;
	}
	template<unsigned int N>
	using bitset = uint8_t[requiredBytes(N)];

	bool bitset_test(uint8_t *bitset, unsigned int bit) {
		return bitset[bit / 8] & 1 << (bit % 8);
	}
	void bitset_set(uint8_t *bitset, unsigned  int bit) {
		bitset[bit / 8] |= 1 << (bit % 8);
	}

	// BITMASK
	/**
	 * Generates a bitmask like Verilog bits[h:l] where 1
	 * represents the selected bits
	 * BITMASK(3, 1) = 0b00001110
	 */
	template <typename WORD_SZ>
	constexpr WORD_SZ bitmask(uint8_t highBit, uint8_t lowBit) {
		unsigned i = ~0U;
		return ~(i << highBit << 1) & (i << lowBit);
	}
}