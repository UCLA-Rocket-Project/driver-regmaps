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
TEST(merge_masks_value) {
	auto mergeResult1 = mergeMasks<WORD_BYTE_H, WORD_BYTE_L>(0x12, 0x21);
	ASSERT_EQUAL(mergeResult1, 0x1221);
	auto mergeResult2 = mergeMasks<HIGH_BIT, MID_NIBBLE, LOW_BIT>(1, 2, 1);
	ASSERT_EQUAL(mergeResult2, 0b10001001);
}
TEST_MAIN()