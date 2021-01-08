#include <ms5611/ms5611.h>
#include <regmap/byteorder.h>

int ms5611_reset(struct reg_bus* dev)
{
	return dev->reg_write(dev->dev_data, MS5611_CMD_RESET, 0, NULL);
}

int ms5611_read_prom(enum ms5611_prom_field field, uint16_t* val, struct reg_bus *dev)
{
	int r = dev->reg_read(dev->dev_data, MS5611_CMD_PROM_READ | (field << 1), 2, (uint8_t*)val);
	if(r < 0) {
		return r;
	}
	*val = sys_be16_to_cpu(*val);
	return 0;
}

int ms5611_start_press_conv(enum ms5611_osr_rate osrRate, struct reg_bus* dev)
{
	return dev->reg_write(dev->dev_data, MS5611_CMD_D1 | (osrRate << 1), 0, NULL);
}

int ms5611_start_temp_conv(enum ms5611_osr_rate osrRate, struct reg_bus* dev)
{
	return dev->reg_write(dev->dev_data, MS5611_CMD_D2 | (osrRate << 1), 0, NULL);
}

int ms5611_read_conv(uint32_t *val, struct reg_bus* dev)
{
	uint8_t adcValue[3];
	int r = dev->reg_read(dev->dev_data, MS5611_CMD_ADC_READ, 3, adcValue);
	if(r < 0) {
		return r;
	}
	*val = sys_get_be24(adcValue);
	return 0;
}