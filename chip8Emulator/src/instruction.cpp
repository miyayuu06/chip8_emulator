#include "instruction.h"

#include <iostream>
#include <cassert>

namespace chip8 {
	std::string Instruction::decode(uint16_t ins, uint16_t& programCounter, Registers& registers, Display& display, Timer& delay, Timer& sound) {
		int insType = ins >> 12;
		std::string type;
		switch (insType) {
		case 0:
			switch (ins & 0xF00) {
			case 0:
				if (ins & 0xF) {
				} else {
					OP_00E0(display);
				}
				break;
			default:
				std::cout << "SYS addr" << std::endl;
			}
			type = "Display things";
			break;
		case 1:
			type = "Jump";
			OP_1nnn(ins, programCounter);
			break;
		/*case 2:
			type = "Call sub";
			break; */
		case 3:
			type = "Stand skip";
			OP_3xkk(ins, programCounter, registers);
			break;
		case 4:
			type = "Skip Neq";
			OP_4xkk(ins, programCounter, registers);
			break;
		case 5:
			type = "Skip eq";
			OP_5xy0(ins, programCounter, registers);
			break;
		case 6:
			type = "Set reg";
			OP_6xkk(ins, registers);
			break;
		/*case 7:
			type = "Add value";
			break;*/
		case 8:
			type = "Byte operations";
			switch (ins & 0xF) {
			case 0:
				OP_8xy0(ins, registers);
				break;
			case 4:
				OP_8xy4(ins, registers);
				break;
			case 5:
				OP_8xy5(ins, registers);
				break;
			default:
				std::cout << std::endl << 8 << " " << +(ins & 0xF) << std::endl;
				assert(0);
				break;
			}
			break;
		/*case 9:
			type = "CPU stuff";
			break;*/
		case 10:
			type = "A instruction";
			OP_Annn(ins, registers);
			break;
		case 15:
			type = "F instruction";
			std::cout << "Type " << +((ins & 0xF0) >> 4) << " " << +(ins & 0xF) << " ";
			switch ((ins & 0xF0) >> 4) {
			case 0:
				if ((ins & 0xF) == 0x7) {
					OP_Fx07(ins, registers, delay);
				}
			case 1:
				if ((ins & 0xF) == 0xE) {
					//OP_Fx1E(ins, registers);
				}
			}
			break;
		default:
			std::cout << std::endl << insType << std::endl;
			assert(0);
			break;
		}
		return type;
	}

	// Instruction with unique first digit

	void Instruction::OP_00E0(Display& display) {
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 32; j++) {
				display.write(i, j, false);
			}
		}
	}

	void Instruction::OP_1nnn(uint16_t operationCode, uint16_t& programCounter) {
		programCounter = (operationCode & 0xFFF);
	}

	//void Instruction::OP_2nnn() {
	//	_SP++;
	//	_PC = _opcode & 0xFFFu;
	//}

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

	//void Instruction::OP_7xkk() {
	//	uint8_t Vx = (_opcode & 0xF00) >> 8u;
	//	uint16_t kk = _opcode & 0xFF;

	//	_registers[Vx] += kk;
	//}

	//void Instruction::OP_9xy0() {
	//	uint8_t Vx = (_opcode & 0xF00) >> 8u;
	//	uint16_t Vy = (_opcode & 0xF0) >> 4u;

	//	if (_registers[Vx] != _registers[Vy]) {
	//		_PC += 2;
	//	}
	//}

	void Instruction::OP_Annn(uint16_t operationCode, Registers& reg) {
		reg.write(0xF, operationCode & 0xFFF);
	}

	//void Instruction::OP_Bnnn() {}

	//void Instruction::OP_Cxkk() {}

	//void Instruction::OP_Dxyn() {}

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
		uint16_t result = reg.read(Vx) + reg.read(Vy);

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

		/*_registers[0xF] = (_registers[Vx] < _registers[Vy]);
		_registers[Vx] = _registers[Vy] - _registers[Vx];*/
	}

	void Instruction::OP_8xyE(uint16_t operationCode, Registers& reg) {
		uint8_t Vx = (operationCode & 0xF00) >> 8;
		uint8_t Vy = (operationCode & 0xF0) >> 4;

		/*_registers[0xF] = _registers[Vx] & 1;
		_registers[Vx] <= 1;*/
	}

	/* F type instructions */

	void Instruction::OP_Fx07(uint16_t operationCode, Registers& reg, Timer& delay) {
		reg.write((operationCode & 0xF00) >> 8, delay.read());
	}

	void Instruction::OP_Fx1E(uint16_t operationCode, Registers& reg) {
		uint16_t result = reg.read(0xF) + reg.read((operationCode & 0xF00) >> 12);
		reg.write(0xF, result);
	}
}