#ifndef BITMASK_H
#define BITMASK_H

/**
 * Generates a bitmask like Verilog bits[h:l] where zero
 * represents the selected bits
 * BITMASK(3, 1) = 0b00001110
 */
#define BITMASK(h, l) ( ~(~0 << (h - l + 1)) << l )

#endif