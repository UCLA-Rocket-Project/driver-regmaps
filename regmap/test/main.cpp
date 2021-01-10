#include "unit_test_framework.h"
#include "test_common.h"
#include <regmap/regmap.h>
using namespace regmap;

TEST(shift_in_bitmask) {
	ASSERT_EQUAL(shiftInValue<WORD_BYTE_H>(0x69), 0x6900);
	ASSERT_EQUAL(shiftInValue<WORD_BYTE_L>(0x69), 0x0069);
}
TEST(shift_out_bitmask) {
	ASSERT_EQUAL(shiftOutValue<WORD_BYTE_H>(0x6900), 0x69);
	ASSERT_EQUAL(shiftOutValue<WORD_BYTE_H>(0x0069), 0x00);
	ASSERT_EQUAL(shiftInValue<WORD_BYTE_L>(0x6900), 0x00);
	ASSERT_EQUAL(shiftInValue<WORD_BYTE_L>(0x0069), 0x69);
}

TEST_MAIN()