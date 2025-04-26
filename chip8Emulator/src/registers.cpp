#include "registers.h"

namespace chip8 {
	Registers::Registers() {
	}

	Registers::~Registers() {
	}

	uint8_t Registers::read(uint8_t Reg) {
		return _register[Reg];
	}

	void Registers::write(uint8_t Reg, uint8_t value) {
		_register[Reg] = value;
	}
}