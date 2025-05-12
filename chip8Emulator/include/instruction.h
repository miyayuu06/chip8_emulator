#pragma once
#include "registers.h"
#include "display.h"
#include "timer.h"

#include <string>

namespace chip8 {
	class Instruction {
	public:
		static std::string decode(uint16_t, uint16_t&, Registers&, Display&, Timer& delay, Timer& sound);

		static void OP_00E0(Display& display);
		//static void OP_00EE();

		//// "First digit is unique" instructions

		static void OP_1nnn(uint16_t operationCode, uint16_t& programCounter);
		//static void OP_2nnn();
		static void OP_3xkk(uint16_t operationCode, uint16_t& programCounter, Registers& registers);
		static void OP_4xkk(uint16_t operationCode, uint16_t& programCounter, Registers& registers);
		static void OP_5xy0(uint16_t operationCode, uint16_t& programCounter, Registers& registers);
		static void OP_6xkk(uint16_t operationCode, Registers&);
		//static void OP_7xkk();
		//static void OP_9xy0();
		static void OP_Annn(uint16_t operationCode, Registers&);
		//static void OP_Bnnn();
		//static void OP_Cxkk();
		//static void OP_Dxyn();

		// "First digit is 8" instructions

		static void OP_8xy0(uint16_t operationCode, Registers& reg);
		static void OP_8xy1(uint16_t operationCode, Registers& reg);
		static void OP_8xy2(uint16_t operationCode, Registers& reg);
		static void OP_8xy3(uint16_t operationCode, Registers& reg);
		static void OP_8xy4(uint16_t operationCode, Registers& reg);
		static void OP_8xy5(uint16_t operationCode, Registers& reg);
		static void OP_8xy6(uint16_t operationCode, Registers& reg);
		static void OP_8xy7(uint16_t operationCode, Registers& reg);
		static void OP_8xyE(uint16_t operationCode, Registers& reg);

		/* F instructions */

		static void OP_Fx07(uint16_t operationCode, Registers& reg, Timer& delay);
		static void OP_Fx0A();
		static void OP_Fx15();
		static void OP_Fx18();
		static void OP_Fx1E(uint16_t operationCode, Registers& reg);
		static void OP_Fx29();
	};
}