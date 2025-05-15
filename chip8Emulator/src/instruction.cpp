#include "instruction.h"

#include <iostream>
#include <Windows.h>

namespace chip8 {
	// Instruction with unique first digit

	void Instruction::OP_00E0(Display& display) {
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 64; j++) {
				display.write(i, j, false);
			}
		}
	}

	void Instruction::OP_00EE(uint16_t& programCounter, Stack& stack) {
		programCounter = stack.pop(); 
	}

	void Instruction::OP_1nnn(uint16_t operationCode, uint16_t& programCounter) {
		programCounter = (operationCode & 0xFFF);
	}

	void Instruction::OP_2nnn(uint16_t operationCode, uint16_t& programCounter, Stack& stack) {
		stack.push(programCounter);
		programCounter = operationCode & 0xFFF;
	}

	void Instruction::OP_3xkk(uint16_t operationCode, uint16_t& programCounter, Registers& reg) {
		if (reg.read((operationCode & 0xF00) >> 8u) == (operationCode & 0xFF)) {
			programCounter += 2;
		}
	}

	void Instruction::OP_4xkk(uint16_t operationCode, uint16_t& programCounter, Registers& reg) {
		if (reg.read((operationCode & 0xF00) >> 8u) != (operationCode & 0xFF)) {
			programCounter += 2;
		}
	}

	void Instruction::OP_5xy0(uint16_t operationCode, uint16_t& programCounter, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8u;
		uint16_t Vy = (operationCode & 0xF0) >> 4u;

		if (reg.read(Vy) == reg.read(Vy)) {
			programCounter += 2;
		}
	}

	void Instruction::OP_6xkk(uint16_t operationCode, Registers& registers) {
		registers.write((operationCode & 0xF00) >> 8, operationCode & 0xFF);
	}

	void Instruction::OP_7xkk(uint16_t operationCode, Registers& registers) {
		uint8_t Vx = (operationCode & 0xF00) >> 8u;
		uint16_t result = registers.read(Vx) + (operationCode & 0xFF);

		registers.write(Vx, result);
	}

	//void Instruction::OP_9xy0() {
	//	uint8_t Vx = (_opcode & 0xF00) >> 8u;
	//	uint16_t Vy = (_opcode & 0xF0) >> 4u;

	//	if (_registers[Vx] != _registers[Vy]) {
	//		_PC += 2;
	//	}
	//}

	void Instruction::OP_Annn(uint16_t operationCode, Registers& reg) {
		reg.iWrite(operationCode & 0xFFF);
	}

	//void Instruction::OP_Bnnn() {}

	void Instruction::OP_Cxkk(uint16_t operationCode, Registers&) {
		uint16_t result = (operationCode & 0xFF) & (std::rand() % 256);
	}

	void Instruction::OP_Dxyn(uint16_t operationCode, Registers& reg, Display& display, Memory& memory) {
		uint16_t x = reg.read((operationCode & 0xF00) >> 8) % 32;
		uint16_t y = reg.read((operationCode & 0xF0) >> 4) % 64;
		reg.write(0xF, 0);
		uint8_t n = operationCode & 0xF;
		uint16_t address = reg.iRead();

		for (int i = 0; i < n; i++) {
			uint8_t spriteByte = memory.readByte(address + i);
			for (int j = 0; j < 8; j++) {
				std::cout << (x + i) << " " << (y + j) << std::endl;
				bool result =  spriteByte & (0x80 >> j);
				bool displayPixel = display.read((x + i) % 32, (y + j) % 64);
				if (result) {
					reg.write(0xF, 1);
				}
				display.write((x + i) % 32, (y + j) % 64, result ^ displayPixel);
			}
		}
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 64; j++) {
				std::cout << display.read(i, j);
			}
			std::cout << std::endl;
		}
	}

	/* 8 type instructions */

	void Instruction::OP_8xy0(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;

		reg.write(Vx, reg.read(Vy));
	}

	void Instruction::OP_8xy1(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;

		reg.write(Vx, reg.read(Vx) | reg.read(Vy));
	}

	void Instruction::OP_8xy2(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;

		reg.write(Vx, reg.read(Vx) & reg.read(Vy));
	}

	void Instruction::OP_8xy3(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;

		reg.write(Vx, reg.read(Vx) ^ reg.read(Vy));
	}

	void Instruction::OP_8xy4(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;
		int result = reg.read(Vx) + reg.read(Vy);

		reg.write(0xF, result / 256);
		reg.write(Vx, result & 0xFF);
	}

	void Instruction::OP_8xy5(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;
		uint16_t result = reg.read(Vx) - reg.read(Vy);
		reg.write(0xF, result > 0);
		reg.write(Vx, result);
	}

	void Instruction::OP_8xy6(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;

		/*_registers[0xF] = _registers[Vx] & 1;
		_registers[Vx] >= 1;*/
	}

	void Instruction::OP_8xy7(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;
		int result = reg.read(Vy) - reg.read(Vx);

		reg.write(0xF, result < 0);
		reg.write(Vx, result);

		/*_registers[0xF] = (_registers[Vx] < _registers[Vy]);
		_registers[Vx] = _registers[Vy] - _registers[Vx];*/
	}

	void Instruction::OP_8xyE(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;

		/*_registers[0xF] = _registers[Vx] & 1;
		_registers[Vx] <= 1;*/
	}

	/* E type instructions */

	void Instruction::OP_Ex9E(uint16_t ins, uint16_t& programCounter, Registers& reg, Keypad& keypad) {
		uint16_t key = reg.read((ins & 0xF00) >> 8);
		if (keypad.read(key)) {
			programCounter += 2;
		}
	}

	void Instruction::OP_ExA1(uint16_t ins, uint16_t& programCounter, Registers& reg, Keypad& keypad) {
		uint16_t key = reg.read((ins & 0xF00) >> 8);
		if (!keypad.read(key)) {
			programCounter += 2;
		}
	}

	/* F type instructions */

	void Instruction::OP_Fx07(uint16_t operationCode, Registers& reg, Timer& delay) {
		reg.write((operationCode & 0xF00) >> 8, delay.read());
	}

	void Instruction::OP_Fx1E(uint16_t operationCode, Registers& reg) {
		uint16_t result = reg.iRead() + reg.read((operationCode & 0xF00) >> 8);
		reg.iWrite(result);
	}
}