#include "regmap/regmap.h"

int reg_read(struct reg_field *field, uint8_t *val, struct reg_bus *dev)
{
	int r = dev->reg_read(dev->dev_data, field->reg, 1, val);
	if(r < 0) {
		return r;
	}
	if(field->mask == 0xFF) {
		return 0;
	}
	*val = (*val & field->mask) >> field->lsb;
	return 0;
}

int reg_write(struct reg_field *field, uint8_t val, struct reg_bus *dev)
{
	uint8_t actualValue;
	// in the case where the mask is the whole bit, we can just write the whole thing at once
	if(field->mask == 0xFF) {
		return dev->reg_write(dev->dev_data, field->reg, 1, &val);
	}
	// else, we have to read in the current bit, apply masking, and write it back out
	int r = dev->reg_read(dev->dev_data, field->reg, 1, &actualValue);
	if(r < 0) {
		return r;
	}
	actualValue = (actualValue & ~field->mask) | ( (val << field->lsb) & field->mask);
	r = dev->reg_write(dev->dev_data, field->reg, 1, &actualValue);
	if(r < 0) {
		return r;
	}
	return 0;
}