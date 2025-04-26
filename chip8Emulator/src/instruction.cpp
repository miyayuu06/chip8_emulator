/*

namespace Instruction {
	// Instruction with unique first digit

	void Instruction::OP_1nnn() {
		_PC = _opcode & 0xFFFu;
	}

	void Instruction::OP_2nnn() {
		_SP++;
		_PC = _opcode & 0xFFFu;
	}

	void Instruction::OP_3xkk() {
		uint8_t Vx = (_opcode & 0xF00) >> 8u;
		uint16_t kk = _opcode & 0xFF;

		if (_registers[Vx] == kk) {
			_PC += 2;
		}
	}

	void Instruction::OP_4xkk() {
		uint8_t Vx = (_opcode & 0xF00) >> 8u;
		uint16_t kk = _opcode & 0xFF;

		if (_registers[Vx] != kk) {
			_PC += 2;
		}
	}

	void Instruction::OP_5xy0() {
		uint8_t Vx = (_opcode & 0xF00) >> 8u;
		uint16_t Vy = (_opcode & 0xF0) >> 4u;

		if (_registers[Vx] == _registers[Vy]) {
			_PC += 2;
		}
	}

	void Instruction::OP_6xkk() {
		uint8_t Vx = (_opcode & 0xF00) >> 8u;
		uint16_t kk = _opcode & 0xFF;

		_registers[Vx] = kk;
	}

	void Instruction::OP_7xkk() {
		uint8_t Vx = (_opcode & 0xF00) >> 8u;
		uint16_t kk = _opcode & 0xFF;

		_registers[Vx] += kk;
	}

	void Instruction::OP_9xy0() {
		uint8_t Vx = (_opcode & 0xF00) >> 8u;
		uint16_t Vy = (_opcode & 0xF0) >> 4u;

		if (_registers[Vx] != _registers[Vy]) {
			_PC += 2;
		}
	}

	void Instruction::OP_Annn() {}

	void Instruction::OP_Bnnn() {}

	void Instruction::OP_Cxkk() {}

	void Instruction::OP_Dxyn() {}

	// Instructions that begin with 8

	void Instruction::OP_8xy0() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;

		_registers[Vx] = _registers[Vy];
	}

	void Instruction::OP_8xy1() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;

		_registers[Vx] |= _registers[Vy];
	}

	void Instruction::OP_8xy2() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;

		_registers[Vx] &= _registers[Vy];
	}

	void Instruction::OP_8xy3() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;

		_registers[Vx] ^= _registers[Vy];
	}

	void Instruction::OP_8xy4() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;
		uint16_t result = _registers[Vx] + _registers[Vy];

		_registers[0xF] = result / 256;

		_registers[Vx] = result & 0xFF;
	}

	void Instruction::OP_8xy5() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;


		_registers[0xF] = (_registers[Vx] > _registers[Vy]);
		_registers[Vx] -= _registers[Vy];
	}

	void Instruction::OP_8xy6() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;

		_registers[0xF] = _registers[Vx] & 1;
		_registers[Vx] >= 1;
	}

	void Instruction::OP_8xy7() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;

		_registers[0xF] = (_registers[Vx] < _registers[Vy]);
		_registers[Vx] = _registers[Vy] - _registers[Vx];
	}

	void Instruction::OP_8xyE() {
		uint8_t Vx = (_opcode & 0xF00u) >> 8u;
		uint8_t Vy = (_opcode & 0xF0u) >> 4u;

		_registers[0xF] = _registers[Vx] & 1;
		_registers[Vx] <= 1;
	}
} */