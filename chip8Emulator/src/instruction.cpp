#include "instruction.h"

#include <iostream>
#include <cassert>

namespace chip8 {
	std::string Instruction::decode(uint16_t ins, uint16_t& programCounter, Registers& registers) {
		int insType = ins >> 12;
		std::string type;
		switch (insType) {
		case 0:
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
			/*
		case 4:
			type = "Skip Neq";
			break;
		case 5:
			type = "Skip Eq";
			break;*/
		case 6:
			type = "Set reg";
			OP_6xkk(ins, registers);
			break;
		/*case 7:
			type = "Add value";
			break;
		case 8:
			type = "Byte operations";
			break;
		case 9:
			type = "CPU stuff";
			break;
		case 15:
			type = "F instruction";
			break;*/
		default:
			std::cout << insType << std::endl;
			assert(0);
			break;
		}
		return type;
	}

	// Instruction with unique first digit

	void Instruction::OP_1nnn(uint16_t operationCode, uint16_t& programCounter) {
		programCounter = (operationCode & 0xFFF);
	}

	//void Instruction::OP_2nnn() {
	//	_SP++;
	//	_PC = _opcode & 0xFFFu;
	//}

	void Instruction::OP_3xkk(uint16_t& operationCode, uint16_t programCounter, Registers& reg) {
		if (reg.read((operationCode & 0xF00) >> 8u) == (operationCode & 0xFF)) {
			programCounter += 2;
		}
	}

	//void Instruction::OP_4xkk() {
	//	uint8_t Vx = (_opcode & 0xF00) >> 8u;
	//	uint16_t kk = _opcode & 0xFF;

	//	if (_registers[Vx] != kk) {
	//		_PC += 2;
	//	}
	//}

	//void Instruction::OP_5xy0() {
	//	uint8_t Vx = (_opcode & 0xF00) >> 8u;
	//	uint16_t Vy = (_opcode & 0xF0) >> 4u;

	//	if (_registers[Vx] == _registers[Vy]) {
	//		_PC += 2;
	//	}
	//}

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

	//void Instruction::OP_Annn() {}

	//void Instruction::OP_Bnnn() {}

	//void Instruction::OP_Cxkk() {}

	//void Instruction::OP_Dxyn() {}

	//// Instructions that begin with 8

	//void Instruction::OP_8xy0() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;

	//	_registers[Vx] = _registers[Vy];
	//}

	//void Instruction::OP_8xy1() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;

	//	_registers[Vx] |= _registers[Vy];
	//}

	//void Instruction::OP_8xy2() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;

	//	_registers[Vx] &= _registers[Vy];
	//}

	//void Instruction::OP_8xy3() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;

	//	_registers[Vx] ^= _registers[Vy];
	//}

	//void Instruction::OP_8xy4() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;
	//	uint16_t result = _registers[Vx] + _registers[Vy];

	//	_registers[0xF] = result / 256;

	//	_registers[Vx] = result & 0xFF;
	//}

	//void Instruction::OP_8xy5() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;


	//	_registers[0xF] = (_registers[Vx] > _registers[Vy]);
	//	_registers[Vx] -= _registers[Vy];
	//}

	//void Instruction::OP_8xy6() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;

	//	_registers[0xF] = _registers[Vx] & 1;
	//	_registers[Vx] >= 1;
	//}

	//void Instruction::OP_8xy7() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;

	//	_registers[0xF] = (_registers[Vx] < _registers[Vy]);
	//	_registers[Vx] = _registers[Vy] - _registers[Vx];
	//}

	//void Instruction::OP_8xyE() {
	//	uint8_t Vx = (_opcode & 0xF00u) >> 8u;
	//	uint8_t Vy = (_opcode & 0xF0u) >> 4u;

	//	_registers[0xF] = _registers[Vx] & 1;
	//	_registers[Vx] <= 1;
	//}
}