#include "registers.h"

namespace chip8 {
	Registers::Registers() {
	}

	Registers::~Registers() {
	}

	uint8_t Registers::read(uint8_t Reg) {
		return (Reg < 16) ? _register[Reg] : 0;
	}

	void Registers::write(uint8_t Reg, uint8_t value) {
		if (Reg < 16) {
			_register[Reg] = value;
		}
	}

	uint16_t Registers::iRead() {
		return I;
	}

	void Registers::iWrite(uint16_t value) {
		I = value;
	}
}