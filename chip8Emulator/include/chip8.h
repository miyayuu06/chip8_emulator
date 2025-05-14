#pragma once
#include "instruction.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>

// Sólo un namespace Chip8

namespace chip8 {
	class Chip8 {
	public:
		const uint16_t PROGRAM_START = 0x200;
		Chip8();
		~Chip8();

		void load_rom(std::string x);
		void cycle();
		std::string decode(uint16_t);

	private:
		Registers _registers;
		Memory _memory;
		Display _display;
		Stack _stack;
		Keypad _keypad;

		uint16_t _PC;

		Timer _delayTimer;
		Timer _soundTimer;
	};
}