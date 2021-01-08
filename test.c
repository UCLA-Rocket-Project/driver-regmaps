#include <stdio.h>
#include "include/regmap.h"
#include "include/bitmask.h"
#include <assert.h>

int mock_read(void *_, uint8_t reg, uint8_t n, uint8_t *vals) {
    for(int i = 0; i < n; i++) {
        vals[i] = 0b10100101;
    }
    return 0;
}
uint8_t writeValue;
int mock_write(void *_, uint8_t reg, uint8_t n, uint8_t *vals) {
    writeValue = vals[0];
    return 0;
}

struct reg_bus mockDev = {
    .reg_read = mock_read,
    .reg_write = mock_write
};

struct reg_field mockField = REG_FIELD(0x5, 4, 2);

int main() {
    // assert that BITMASK works
    assert(BITMASK(5, 2) == 0b00111100);
    assert(BITMASK(7, 0) == 0xFF);
    
    uint8_t val;
    reg_read(&mockField, &val, &mockDev);
    assert(val == 1);

    reg_write(&mockField, 2, &mockDev);
    assert(writeValue == 0b10101001);

    printf("ALL TESTS PASSED\n");
}