#pragma once
#include <array>

namespace chip8 {
	class Display {
	public:
		Display();
		~Display();
		void write(uint8_t row, uint8_t column, bool value);
	private:
		std::array<std::array<bool, 32>, 64> _display;
	};
}