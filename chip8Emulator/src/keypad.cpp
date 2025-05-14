#include "keypad.h"

namespace chip8 {

	Keypad::Keypad() {
		for (int i = 0; i < 16; i++) {
			write(REFERENCE[i], false);
		}
	}
	
	Keypad::~Keypad() {
	}

	int Keypad::read(char character) {
		for (std::pair key : _keyValues) {
			if (key.first == character) {
				return key.second ? 1 : 0;
			}
		}
		return -1;
	}

	void Keypad::write(char character, bool value) {
		for (int i = 0; i < 16; i++) {
			if (_keyValues[i].first == character) {
				_keyValues[i].second = value; 
				return;
			}
		}
	}
}