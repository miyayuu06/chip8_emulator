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

		if (reg.read(Vx) == reg.read(Vy)) {
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

	void Instruction::OP_9xy0(uint16_t operationCode, uint16_t& programCounter, Registers& registers) {
		uint8_t Vx = (operationCode & 0xF00) >> 8u;
		uint16_t Vy = (operationCode & 0xF0) >> 4u;

		if (registers.read(Vx) != registers.read(Vy)) {
			programCounter += 2;
		}
	}

	void Instruction::OP_Annn(uint16_t operationCode, Registers& reg) {
		reg.iWrite(operationCode & 0xFFF);
	}

	//void Instruction::OP_Bnnn() {}

	void Instruction::OP_Cxkk(uint16_t operationCode, Registers&) {
		uint16_t result = (operationCode & 0xFF) & (std::rand() % 256);
	}

	void Instruction::OP_Dxyn(uint16_t operationCode, Registers& reg, Display& display, Memory& memory) {
		uint16_t x = reg.read((operationCode & 0xF00) >> 8);
		uint16_t y = reg.read((operationCode & 0xF0) >> 4);
		reg.write(0xF, 0);
		uint8_t n = operationCode & 0xF;
		uint16_t address = reg.iRead();

		for (int i = 0; i < n; ++i) {
			uint8_t spriteByte = memory.readByte(address + i);
			for (int j = 0; j < 8; ++j) {
				//std::cout << (x + i) << " " << (y + j) << std::endl;
				uint8_t result =  spriteByte & (0x80 >> j);
				uint32_t displayPixel = display.read((y + i) % 32, (x + j) % 64);
				if (result) {
					reg.write(0xF, 1);
					display.write((y + i) % 32, (x + j) % 64, result ^ displayPixel);
				}
				
			}
		}
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 64; j++) {
				std::cout << (display.read(i, j) ? '#' : ' ');
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

		reg.write(0xF, result > 255U);
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
		uint8_t aux = reg.read(Vx);

		reg.write(0xF, aux & 1);
		reg.write(Vx, aux >> 1);
	}

	void Instruction::OP_8xy7(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;
		int result = reg.read(Vy) - reg.read(Vx);

		reg.write(0xF, result > 0);
		reg.write(Vx, result);

	}

	void Instruction::OP_8xyE(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t aux = reg.read(Vx);
			
		reg.write(0xF, (aux & 0x80) >> 7);
		reg.write(Vx, aux << 1);
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

	void Instruction::OP_Fx0A(uint16_t operationCode, uint16_t& programCounter, Registers& reg, Keypad& keypad) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		bool flag = false;
		uint8_t key = 0;
		for (int i = 0; i < 256; i++) {
			if (keypad.read(i)) {
				flag = true; key = i;
				break;
			}
		}
		if (!flag) {
			programCounter -= 2;
		}
		else {
			reg.write(Vx, key);
		}
	}

	void Instruction::OP_Fx15(uint16_t operationCode, Registers& reg, Timer& delay) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		delay.set(reg.read(Vx));
	}

	void Instruction::OP_Fx1E(uint16_t operationCode, Registers& reg) {
		uint16_t result = reg.iRead() + reg.read((operationCode & 0xF00) >> 8);
		reg.iWrite(result);
	}

	/*void Instruction::OP_Fx29();*/


	void Instruction::OP_Fx33(uint16_t operationCode, Registers& reg, Memory& mem) {
		uint8_t Vx = reg.read((operationCode & 0xF00) >> 8);
		uint16_t address = reg.iRead();
		for (uint8_t i = 0; i < 3; ++i) {
			mem.write(address + i, Vx & 0x1);
			Vx >= 1;
		}
	}

	void Instruction::OP_Fx55(uint16_t operationCode, Registers& reg, Memory& mem) {
		uint16_t address = reg.iRead();
		uint8_t x = (operationCode & 0xF00) >> 8;
		for (uint8_t i = 0; i <= x; ++i) {
			mem.write(address + i, reg.read(x));
		}
	}

	void Instruction::OP_Fx65(uint16_t operationCode, Registers& reg, Memory& mem) {
		uint16_t address = reg.iRead();
		uint8_t x = (operationCode & 0xF00) >> 8;
		for (uint8_t i = 0; i <= x; ++i) {
			reg.write(i, mem.readByte(address + i));
		}
	}
}