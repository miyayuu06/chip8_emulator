#pragma once
#include "graphics.h"
#include "registers.h"
#include "display.h"
#include "timer.h"
#include "stack.h"
#include "memory.h"
#include "keypad.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>

// Sólo un namespace Chip8

namespace chip8 {
	struct Chip8 {
	public:
		const uint16_t PROGRAM_START = 0x200;
		Chip8();
		~Chip8();

		int load_rom(std::string x);
		void cycle();
		void program(int programData);

		std::string decode(uint16_t);

		Registers _registers;
		Memory _memory;
		Display _display;
		Stack _stack;
		Keypad _keypad;

		uint16_t _PC;

		Timer _delayTimer;
		Timer _soundTimer;

		Graphics _graphics;
	};
}