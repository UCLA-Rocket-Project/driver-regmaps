#pragma once
#include "adxl375_defs.h"

namespace adxl375 {
	using regmap::Regmap;
	class ADXL375 {
		Regmap<uint8_t, endianfix::endian::big,
			DEVICE_ID
		> regmap;
	};
};