#include "display.h"

namespace chip8 {
	Display::Display() {
		mode = false;
	}

	Display::~Display() {
	}

	bool Display::read(uint8_t row, uint8_t column) {
		return mode ? _display2[row][column] : _display1[row][column];
	}

	void Display::write(uint8_t row, uint8_t column, bool value) {
		if (mode) {
			_display2[row][column] = value;
		}
		else {
			_display1[row][column] = value;
		}
	}

	void Display::setMode(bool isSuper) {
		mode = isSuper;
	}
}