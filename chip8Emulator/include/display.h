#pragma once
#include <array>

namespace chip8 {
	class Display {
	public:
		Display();
		~Display();
		bool read(uint8_t row, uint8_t column);
		void write(uint8_t row, uint8_t column, bool value);
		void setMode(bool isSuper);
	private:
		std::array<std::array<bool, 64>, 32> _display1;
		std::array<std::array<bool, 128>, 64> _display2;
		bool mode;
		uint8_t addOn;
	};
}