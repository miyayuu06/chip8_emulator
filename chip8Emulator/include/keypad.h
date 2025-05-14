#pragma once

#include <array>
#include <string>

namespace chip8 {
	class Keypad {
	public:
		Keypad();
		~Keypad();
		int read(char);
		void write(char, bool);

	private:
		std::array<std::pair<char, bool>, 16> _keyValues;
		const std::string REFERENCE = "1234qwerasdfzxcv";
	};
}