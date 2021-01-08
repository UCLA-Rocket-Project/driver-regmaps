#pragma once
#include <cstdint>

namespace ms5611 {
	enum CMD {
		RESET = 0x1E,
		D1_BASE = 0x40,
		D2_BASE = 0x50,
		ADC_READ = 0x00,
		PROM_READ = 0xA0
	};
	enum PROM_FIELD {
		FACTORY,
		SENSt1,
		OFFt1,
		TCS,
		TCO,
		Tref,
		TEMPSENS,
		CRC,
		__COUNT
	};
	enum OSR {
		RATE_256,
		RATE_512,
		RATE_1024,
		RATE_2048,
		RATE_4096
	};
};