#include "display.h"

namespace chip8 {
	Display::Display() {
	}

	Display::~Display() {
	}

	bool Display::read(uint8_t row, uint8_t column) {
		return _display[row][column];
	}

	void Display::write(uint8_t row, uint8_t column, bool value) {
		_display[row][column] = value;
	}
}