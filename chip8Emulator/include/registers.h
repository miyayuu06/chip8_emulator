#pragma once
#include <cstdint>
#include <array>

namespace chip8 {

	class Registers {
	public:
		Registers();
		~Registers();
		void write(uint8_t, uint8_t);
		uint8_t read(uint8_t);

	private:
		std::array<uint8_t, 16> _register;
		uint16_t _I;
	};

}