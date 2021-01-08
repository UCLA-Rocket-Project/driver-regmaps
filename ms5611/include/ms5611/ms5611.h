#include <regmap/bus.h>
#include <regmap/endianfix.h>
#include <memory>
#include "ms5611_defs.h"

namespace ms5611 {
	class MS5611 {
	public:
		std::shared_ptr<regmap::Bus> bus;
		unsigned int devAddr;
		uint16_t prom[PROM_FIELD::__COUNT];
		bool promRead = false; // we only need to read prom once
		OSR lastOsr;
		CMD lastCmd;

		// intermediate variables for calculating the altitude
		int32_t dT;
		int32_t temp;
		int64_t off;
		int64_t sens;
		int32_t press;

		uint32_t lastTempReading;
		uint32_t lastPressureReading;

		MS5611(std::shared_ptr<regmap::Bus> bus, unsigned int addr):
			bus(std::move(bus)), devAddr(addr) {};

		int reset() {
			return bus->write(devAddr, CMD::RESET, nullptr, 0);
		}
		int readProm() {
			if(promRead) {
				return 1;
			}
			int r;
			for(int i = 0; i < PROM_FIELD::__COUNT; i++) {
				r = bus->read(devAddr, CMD::PROM_READ | (i << 1), (uint8_t*)&prom[i], 2);
				if(r < 0) {
					return r;
				}
				prom[i] = endianfix::fixEndianess<endianfix::endian::big>(prom[i]);
			}
			promRead = true;
			return 0;
		}
		int startPressureConversion(OSR osr) {
			int r;
			r = bus->write(devAddr, CMD::D1_BASE | (osr << 1), 0, NULL);
			if(r < 0) {
				return r;
			}
			lastCmd = CMD::D1_BASE;
			lastOsr = osr;
			return 0;
		}
		int startTempConversion(OSR osr) {
			int r;
			r = bus->write(devAddr, CMD::D2_BASE | (osr << 1), 0, NULL);
			if(r < 0) {
				return r;
			}
			lastCmd = CMD::D2_BASE;
			lastOsr = osr;
			return 0;
		}
		uint32_t sleepDurationUsec() {
			return 1000000 >> (lastOsr + 8);
		}
		int readConversionResult(uint32_t &result) {
			int r;
			endianfix::uint24_t res;
			r = bus->read(devAddr, CMD::ADC_READ, res, 3);
			if(r < 0) {
				return r;
			}
			result = endianfix::fixEndianess<endianfix::endian::big>(res);
			if(lastCmd == D1_BASE) {
				lastPressureReading = result;
				off = (prom[2] << 16) + ((prom[4] * dT) >> 7);
				sens = (prom[1] << 15) + ((prom[3] * dT) >> 8);
				press = (lastPressureReading * (sens >> 21) - off) >> 15;
			}
			else {
				lastTempReading = result;
				dT = lastTempReading - (prom[5] << 8);
				temp = 2000 + ((dT * prom[6]) >> 23);
			}
			return 0;
		}
		float pressure() {
			return press / 100.0;
		}
		float temperature() {
			return temp / 100.0;
		}
	};
}