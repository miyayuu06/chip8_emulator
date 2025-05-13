#pragma once
#include "instruction.h"

#include <iostream>
#include <vector>
#include <fstream>

// Sólo un namespace Chip8

namespace chip8 {
	class Chip8 {
	public:
		const uint16_t PROGRAM_START = 0x200;
		Chip8();
		~Chip8();

		void load_rom(std::string x);
		void cycle();

		Registers _registers;
		Memory _memory;
		Display _display;
		Stack _stack;

		uint8_t* _keypad;

		uint16_t _PC;

		Timer _delayTimer;
		Timer _soundTimer;
	private:
	};

	class Keypad {
	public:
	};
}