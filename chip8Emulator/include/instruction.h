#pragma once
#include "chip8.h"

#include <string>

namespace chip8 {
	class Chip8;
	class Instruction {
	public:
		
		// Special operations for operating on Vx and Vy
		static uint8_t getVx(uint16_t& operationCode);
		static uint8_t getVy(uint16_t& operationCode);

		/* Implementación con interfaz uniforme */

		static void OP_00E0(uint16_t operationCode, Chip8& chip);
		static void OP_00EE(uint16_t operationCode, Chip8& chip);

		// "First digit is unique" instructions

		static void OP_1nnn(uint16_t operationCode, Chip8& chip);
		static void OP_2nnn(uint16_t operationCode, Chip8& chip);
		static void OP_3xkk(uint16_t operationCode, Chip8& chip);
		static void OP_4xkk(uint16_t operationCode, Chip8& chip);
		static void OP_5xy0(uint16_t operationCode, Chip8& chip);
		static void OP_6xkk(uint16_t operationCode, Chip8& chip);
		static void OP_7xkk(uint16_t operationCode, Chip8& chip);
		static void OP_9xy0(uint16_t operationCode, Chip8& chip);
		static void OP_Annn(uint16_t operationCode, Chip8& chip);
		static void OP_Bnnn(uint16_t operationCode, Chip8& chip);
		static void OP_Cxkk(uint16_t operationCode, Chip8& chip);
		static void OP_Dxyn(uint16_t operationCode, Chip8& chip);

		// "First digit is 8" instructions

		static void OP_8xy0(uint16_t operationCode, Chip8& chip);
		static void OP_8xy1(uint16_t operationCode, Chip8& chip);
		static void OP_8xy2(uint16_t operationCode, Chip8& chip);
		static void OP_8xy3(uint16_t operationCode, Chip8& chip);
		static void OP_8xy4(uint16_t operationCode, Chip8& chip);
		static void OP_8xy5(uint16_t operationCode, Chip8& chip);
		static void OP_8xy6(uint16_t operationCode, Chip8& chip);
		static void OP_8xy7(uint16_t operationCode, Chip8& chip);
		static void OP_8xyE(uint16_t operationCode, Chip8& chip);

		/* E instructions */

		static void OP_Ex9E(uint16_t operationCode, Chip8& chip);
		static void OP_ExA1(uint16_t operationCode, Chip8& chip);

		/* F instructions */

		static void OP_Fx07(uint16_t operationCode, Chip8& chip);
		static void OP_Fx0A(uint16_t operationCode, Chip8& chip);
		static void OP_Fx15(uint16_t operationCode, Chip8& chip);
		static void OP_Fx18(uint16_t operationCode, Chip8& chip);
		static void OP_Fx1E(uint16_t operationCode, Chip8& chip);
		static void OP_Fx29(uint16_t operationCode, Chip8& chip);
		static void OP_Fx33(uint16_t operationCode, Chip8& chip);
		static void OP_Fx55(uint16_t operationCode, Chip8& chip);
		static void OP_Fx65(uint16_t operationCode, Chip8& chip);

		/* SuperChip instructions */

		static void OP_00FE(uint16_t operationCode, Chip8& chip);
		static void OP_00FF(uint16_t operationCode, Chip8& chip);
		static void OP_00CN(uint16_t operationCode, Chip8& chip);
		static void OP_00FB(uint16_t operationCode, Chip8& chip);
		static void OP_00FC(uint16_t operationCode, Chip8& chip);
		static void OP_00FD(uint16_t operationCode, Chip8& chip);

		static void OP_FX30(uint16_t operationCode, Chip8& chip);
		static void OP_FX75(uint16_t operationCode, Chip8& chip);
		static void OP_FX85(uint16_t operationCode, Chip8& chip);

	};
}