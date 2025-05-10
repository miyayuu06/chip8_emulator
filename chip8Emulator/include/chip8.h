#pragma once

#include "memory.h"
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

		uint32_t _opcode;

		Registers _registers;
		Memory _memory;
		uint8_t* _keypad;

		uint16_t _PC;
		uint16_t* _stack;
		uint8_t _SP;

		/* timer::Timer _delayTimer;
		timer::Timer _soundTimer; */
	private:
	};

	/*class Timer {
	public:
		Timer();


		uint8_t _value;
	};*/

	class Stack {
	public:

	};

	class Keypad {
	public:
	};
}