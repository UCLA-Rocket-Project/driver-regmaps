#pragma once

namespace regmap {
	/**
	 * Implements a bus which can send and receive bytes
	 */
	class Bus {
	public:
		virtual int xfer(unsigned int deviceAddr, unsigned int readBytes, unsigned int writeBytes);
		int read(unsigned int deviceAddr, unsigned int readBytes) {
			return xfer(deviceAddr, readBytes, 0);
		};
		int write(unsigned int deviceAddr, unsigned int writeBytes) {
			return xfer(deviceAddr, 0, writeBytes);
		};
		virtual ~Bus() = default;
	};
}