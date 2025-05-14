#pragma once
#include <array>

namespace chip8 {
	class Display {
	public:
		Display();
		~Display();
		bool read(uint8_t row, uint8_t column);
		void write(uint8_t row, uint8_t column, bool value);
	private:
		std::array<std::array<bool, 64>, 32> _display;
	};
}