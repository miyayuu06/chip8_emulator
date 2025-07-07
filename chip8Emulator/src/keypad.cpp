#include "keypad.h"
#include <Windows.h>

namespace chip8 {

	Keypad::Keypad() {
		reset();
	}
	
	Keypad::~Keypad() {
	}

	int Keypad::read(char character) {
		return (character < 16) ? _keyValues[character] : 0;
	}

	void Keypad::cycleRead() {
		for (int i = 0; i < 16; i++) {
			if (GetAsyncKeyState(_KEYREFERENCE[i]) & 0x8000) {
				_keyValues[i] = true;
			}
			else {
				_keyValues[i] = false;
			}
		}
	}

	void Keypad::write(uint8_t character, bool value) {
		if (character < 16) {
			_keyValues[character] = value;
		}
	}

	void Keypad::reset() {
		for (int i = 0; i < 16; i++) {
			_keyValues[i] = false;
		}
	}
}