#pragma once
#include "registers.h"
#include <string>

namespace chip8 {
	class Instruction {
	public:
		static std::string decode(uint16_t, uint16_t&, Registers&);

		//void OP_0nnn();

		//// "First digit is unique" instructions

		static void OP_1nnn(uint16_t operationCode, uint16_t& programCounter);
		//void OP_2nnn();
		static void OP_3xkk(uint16_t& operationCode, uint16_t programCounter, Registers& registers);
		//void OP_4xkk();
		//void OP_5xy0();
		static void OP_6xkk(uint16_t operationCode, Registers&);
		//void OP_7xkk();
		//void OP_9xy0();
		//void OP_Annn();
		//void OP_Bnnn();
		//void OP_Cxkk();
		//void OP_Dxyn();

		//// "First digit is 8" instructions

		//void OP_8xy0();
		//void OP_8xy1();
		//void OP_8xy2();
		//void OP_8xy3();
		//void OP_8xy4();
		//void OP_8xy5();
		//void OP_8xy6();
		//void OP_8xy7();
		//void OP_8xyE();
	};
}