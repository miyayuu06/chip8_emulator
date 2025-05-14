#include "keypad.h"
#include <Windows.h>

namespace chip8 {

	Keypad::Keypad() {
		reset();
	}
	
	Keypad::~Keypad() {
	}

	int Keypad::read(char character) {
		for (int i = 0; i < 256; i++) {
			if (i == character) {
				return _keyValues[i];
			}
		}
		return -1;
	}

	void Keypad::cycleRead() {
		for (int i = 0; i < 256; i++) {
			if (GetAsyncKeyState(i) & 0x8000) {
				write(i, true);
			}
		}
	}

	void Keypad::write(char character, bool value) {
		for (int i = 0; i < 256; i++) {
			if (i == character) {
				_keyValues[i] = value; 
				return;
			}
		
		}
	}

	void Keypad::reset() {
		for (int i = 0; i < 256; i++) {
			_keyValues[i] = false;
		}
	}
}