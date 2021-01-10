#include "test_common.h"
#include <type_traits>

/*
 * Because we've abused constexpr, most tests can be
 * compile-time checked:
 */

/* check addr access */
static_assert(RegAddr<ZERO_REG>() == 0, "address access");
static_assert(RegAddr<ONE_REG>() == 1, "address access");
static_assert(RegAddr<WORD_REG>() == 0x10, "address access");

/* check backing types */
static_assert(std::is_same<RegType<ZERO_REG>, uint8_t>::value, "backing types");
static_assert(std::is_same<RegType<ONE_REG>, uint8_t>::value, "backing types");
static_assert(std::is_same<RegType<WORD_REG>, uint16_t>::value, "backing types");

/* check mask behavior */
static_assert(bitmask<WORD_BYTE_H>() == 0xFF00,
              "bitmask");
static_assert(bitmask<WORD_BYTE_L>() == 0xFF,
              "bitmask");
static_assert(bitmask<MID_NIBBLE>() == 0b00111100,
              "bitmask");
