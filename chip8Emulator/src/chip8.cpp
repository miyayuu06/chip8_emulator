#include "chip8.h"
#include "instruction.h"

#include <filesystem>
#include <cassert>

namespace chip8 {
	Chip8::Chip8() {
		_PC = Chip8::PROGRAM_START;
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
			_graphics.draw(_display);
			cycle();
			Sleep(1000/60);


		}


	}

	std::string Chip8::decode(uint16_t ins) {
		int insType = ins >> 12;
		std::string type = "";
		//std::cout << ((ins & 0xF000) >> 12) << " " << ((ins & 0xF00) >> 8) << " " << ((ins & 0xF0) >> 4) << " " << (ins & 0xF) << std::endl;
		switch (insType) {
		case 0:
			switch (ins & 0xF00) {
			case 0:
				if ((ins & 0xFF) == 0xEE) {
					Instruction::OP_00EE(ins, *this);
				}
				else {
					Instruction::OP_00E0(ins, *this);
					return "YES";
				}
				break;
			default:
				std::cout << "SYS addr" << std::endl;
				break;
			}
			break;
		case 1:
			Instruction::OP_1nnn(ins, *this);
			break;
		case 2:
			Instruction::OP_2nnn(ins, *this);
			break;
		case 3:
			Instruction::OP_3xkk(ins, *this);
			break;
		case 4:
			Instruction::OP_4xkk(ins, *this);
			break;
		case 5:
			Instruction::OP_5xy0(ins, *this);
			break;
		case 6:
			Instruction::OP_6xkk(ins, *this);
			break;
		case 7:
			Instruction::OP_7xkk(ins, *this);
			break;
		case 8:
			switch (ins & 0xF) {
			case 0:
				Instruction::OP_8xy0(ins, *this);
				break;
			case 1:
				Instruction::OP_8xy1(ins, *this);
				break;
			case 2:
				Instruction::OP_8xy2(ins, *this);
				break;
			case 3:
				Instruction::OP_8xy3(ins, *this);
				break;
			case 4:
				Instruction::OP_8xy4(ins, *this);
				break;
			case 5:
				Instruction::OP_8xy5(ins, *this);
				break;
			case 6:
				Instruction::OP_8xy6(ins, *this);
				break;
			case 7:
				Instruction::OP_8xy7(ins, *this);
				break;
			case 0xE:
				Instruction::OP_8xyE(ins, *this);
				break;
			default:
				assert(8);
				break;
			}
			break;
		case 9:
			Instruction::OP_9xy0(ins, *this);
			break;
		case 0xA:
			Instruction::OP_Annn(ins, *this);
			break;
		case 0xB:
			Instruction::OP_Bnnn(ins, *this);
			break;
		case 0xC:
			Instruction::OP_Cxkk(ins, *this);
			break;
		case 0xD:
			Instruction::OP_Dxyn(ins, *this);
			break;
		case 0xE:
			if ((ins & 0xF) == 0xE) {
				Instruction::OP_Ex9E(ins, *this);
			}
			else {
				Instruction::OP_ExA1(ins, *this);
			}
			break;
		case 0xF:
			switch ((ins & 0xF0) >> 4) {
			case 0:
				if ((ins & 0xF) == 0x7) {
					Instruction::OP_Fx07(ins, *this);
				}
				else if ((ins & 0xF) == 0xA) {
					Instruction::OP_Fx0A(ins, *this);
				}
				else {
					assert(150);
				}
				break;
			case 1:
				if ((ins & 0xF) == 0xE) {
					Instruction::OP_Fx1E(ins, *this);
					break;
				}
				else {
					Instruction::OP_Fx18(ins, *this);
					break;
				}
			case 2:
				Instruction::OP_Fx29(ins, *this);
				break;
			case 3:
				Instruction::OP_Fx33(ins, *this);
				break;
			case 5:
				Instruction::OP_Fx55(ins, *this);
				break;
			case 0x6:
				Instruction::OP_Fx65(ins, *this);
				break;
			default:
				assert(15);
				break;
			}
			break;
		default:
			//std::cout << std::endl << insType << ((ins & 0xF0) >> 4) << std::endl;
			//assert(insType);
			break;
		}
		return type;
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