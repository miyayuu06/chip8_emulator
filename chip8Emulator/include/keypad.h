#pragma once

#include <array>
#include <string>

namespace chip8 {
	class Keypad {
	public:
		Keypad();
		~Keypad();
		int read(char);
		void cycleRead();
		void write(char, bool);
		void reset();

	private:
		std::array<bool, 16> _keyValues;
		const std::string _KEYREFERENCE = "X123QWEASDZC4RFV";
	};
}