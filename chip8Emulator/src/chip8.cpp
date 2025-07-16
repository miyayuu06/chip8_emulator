#include "chip8.h"
#include "instruction.h"

#include <filesystem>
#include <cassert>

namespace chip8 {
	Chip8::Chip8() {
		_PC = Chip8::PROGRAM_START;
		instructionTable = {
			{0xFFFF, 0x00E0, Instruction::OP_00E0},
			{0xFFFF, 0x00EE, Instruction::OP_00EE},
			{0xFFFF, 0x00FE, Instruction::OP_00FE},
			{0xFFFF, 0x00FF, Instruction::OP_00FF},
			{0xF000, 0x1000, Instruction::OP_1nnn},
			{0xF000, 0x2000, Instruction::OP_2nnn},
			{0xF000, 0x3000, Instruction::OP_3xkk},
			{0xF000, 0x4000, Instruction::OP_4xkk},
			{0xF00F, 0x5000, Instruction::OP_5xy0},
			{0xF000, 0x6000, Instruction::OP_6xkk},
			{0xF000, 0x7000, Instruction::OP_7xkk},
			{0xF00F, 0x8000, Instruction::OP_8xy0},
			{0xF00F, 0x8001, Instruction::OP_8xy1},
			{0xF00F, 0x8002, Instruction::OP_8xy2},
			{0xF00F, 0x8003, Instruction::OP_8xy3},
			{0xF00F, 0x8004, Instruction::OP_8xy4},
			{0xF00F, 0x8005, Instruction::OP_8xy5},
			{0xF00F, 0x8006, Instruction::OP_8xy6},
			{0xF00F, 0x8007, Instruction::OP_8xy7},
			{0xF00F, 0x800E, Instruction::OP_8xyE},
			{0xF00F, 0x9000, Instruction::OP_9xy0},
			{0xF000, 0xA000, Instruction::OP_Annn},
			{0xF000, 0xB000, Instruction::OP_Bnnn},
			{0xF000, 0xC000, Instruction::OP_Cxkk},
			{0xF000, 0xD000, Instruction::OP_Dxyn},
			{0xF0FF, 0xE09E, Instruction::OP_Ex9E},
			{0xF0FF, 0xE0A1, Instruction::OP_ExA1},
			{0xF0FF, 0xF007, Instruction::OP_Fx07},
			{0xF0FF, 0xF00A, Instruction::OP_Fx0A},
			{0xF0FF, 0xF015, Instruction::OP_Fx15},
			{0xF0FF, 0xF018, Instruction::OP_Fx18},
			{0xF0FF, 0xF01E, Instruction::OP_Fx1E},
			{0xF0FF, 0xF029, Instruction::OP_Fx29},
			{0xF0FF, 0xF033, Instruction::OP_Fx33},
			{0xF0FF, 0xF055, Instruction::OP_Fx55},
			{0xF0FF, 0xF065, Instruction::OP_Fx65}
		};
	}

	Chip8::~Chip8() {
	}

	int Chip8::load_rom(std::string path) {
		std::ifstream rf(path, std::ios::in | std::ios::binary);
		if (!rf) {
			std::cout << "Can not access file, sowwy!" << std::endl;
			return 0;
		}
		int fileSize = std::filesystem::file_size(path);
		std::vector<uint8_t> programData(fileSize);
		rf.read((char*)programData.data(), fileSize);
		rf.close();
		_memory.write(PROGRAM_START, programData.data(), programData.size());

		/* Clearing display and registers */

		for (int i = 0; i < 16; i++) {
			_registers.write(i, 0);
		}
		Instruction::OP_00E0(0, *this);
		_registers.iWrite(0);

		return programData.size();
	}

	void Chip8::program(int programDataSize) {
		_PC = PROGRAM_START;
		int quit = 0;

		while (!quit) {
			quit = _graphics.update(_keypad);
			_buzzer.update(_soundTimer.read());
			_graphics.draw(_display);
			cycle();
			Sleep(1000/60);
		}

	}


	void Chip8::decode(uint16_t opcode) {
		for (const auto& entry : instructionTable) {
			if ((opcode & entry.mask) == entry.pattern) {
				entry.func(opcode, *this);
				return;
			}
		}

		std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
		throw std::runtime_error("Unknown opcode");
	}


	void Chip8::cycle() {
		for (int i = 0; i < 10; i++) {
			uint16_t operationCode = _memory.read(_PC);
			_PC += 2;

			decode(operationCode);
			/*for (int i = 0; i < 16; i++) {
				std::cout << (i) << " " << +(_registers.read(i)) << " | ";
			}
			std::cout << "I " << _registers.iRead() << std::endl;
			std::cout << std::endl << std::endl;*/
		}

		if (_delayTimer.read() > 0) {
			_delayTimer.decrement();
		}
		if (_soundTimer.read() > 0) {
			_soundTimer.decrement();
		}
	}
};