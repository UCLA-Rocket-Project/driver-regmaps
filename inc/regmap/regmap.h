/*
 * A reduced-size adaptation of the Linux kernel's regmap interface,
 * for use with embedded applications
 */
#pragma once
#ifndef REGMAP_H
#define REGMAP_H
#include <stdbool.h>
#include <stdint.h>
#include <regmap/bitmask.h>

/**
 * Represents a device to which register values will be written
 * Each register is 8-bits wide, with address from [0, 255]
 */
struct regmap_dev_conf {
	/**
	 * NOTES: There are no read/write register protection
	 */
	/**
	 * Reads N bytes from a register
	 * Returns a negative number on error
	 * Not nullable
	 */
	int (*reg_read)(void *dev_data, uint8_t reg, uint8_t n, uint8_t *vals);
	/**
	 * Writes N bytes to a register
	 * Returns a negative number on error
	 * Not nullable
	 */
	int (*reg_write)(void *dev_data, uint8_t reg, uint8_t n, uint8_t *vals);
	/**
	 * An argument to be passed into reg_read/write
	 */
	void *dev_data;
};

/**
 * Description of an register field
 */
struct reg_field {
	/**
	 * The register the field belongs to
	 */
	uint8_t reg;
	/**
	 * A bitmask with 1's for each bit this field encompasses
	 * To represent reg[3:1], set to 
	 * 0b  0  0  0  0  1  1  1  0
	 * (#) 7  6  5  4  3  2  1  0
	 */
	uint8_t mask;
    /**
     * Index of the least significant bit.
     * Will award brownie points if you can figure out how to get the LSB from the mask
     * efficiently.
     */
    uint8_t lsb;
};

/**
 * Reads a value from a register
 * @param field The field to read from
 * @param val Location to store the value of the register
 * @param dev The dev to read the field over
 */
int reg_read(struct reg_field *field, uint8_t *val, struct regmap_dev_conf *dev);
/**
 * Writes a value to a register
 * @param field The field to write to
 * @param val Value to write
 * @param dev The dev to read the field over
 */
int reg_write(struct reg_field *field, uint8_t val, struct regmap_dev_conf *dev);
/**
 * Burst reads N registers from a device
 */
inline int burst_read(uint8_t reg, uint8_t n, uint8_t *vals, struct regmap_dev_conf *dev)
{
	return dev->reg_read(dev->dev_data, reg, n, vals);
}
/**
 * Burst writes N registers to a device
 */
inline int burst_write(uint8_t reg, uint8_t n, uint8_t *vals, struct regmap_dev_conf *dev)
{
	return dev->reg_write(dev->dev_data, reg, n, vals);
}
/**
 * Convinience header for defining a REG_FIELD
 */
#define REG_FIELD( REG, HIGH, LOW ) { .reg=REG, .mask=BITMASK(HIGH, LOW), .lsb=LOW}
#endif