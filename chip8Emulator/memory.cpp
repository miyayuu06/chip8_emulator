#include "memory.h"

namespace chip8 {
	Memory::Memory() {
	}

	Memory::~Memory() {
	}

	uint8_t Memory::read(uint16_t address) {
		return _space[address];
	}

	void Memory::write(uint16_t address, uint8_t data) {
		_space[address] = data;
	}

	void Memory::write(uint32_t address, const uint8_t* data, size_t dataSizeInBytes) {
		std::memcpy(&_space[address], data, dataSizeInBytes);
	}
}