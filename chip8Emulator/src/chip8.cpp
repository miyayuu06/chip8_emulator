#include "chip8.h"
#include <filesystem>
#include <Windows.h>

#include <cassert>

namespace chip8 {
	Chip8::Chip8() {
		_keypad = new uint8_t[16];

		_PC = Chip8::PROGRAM_START;
	}

	Chip8::~Chip8() {
		delete[] _keypad;
	}

	void Chip8::load_rom(std::string path) {
		std::ifstream rf(path, std::ios::out | std::ios::binary);
		if (!rf) {
			std::cout << "Can not access file, sowwy!" << std::endl;
			return;
		}
		int fileSize = std::filesystem::file_size(path);
		std::vector<uint8_t> programData(fileSize);
		rf.read((char*)programData.data(), fileSize);
		rf.close();
		_memory.write(PROGRAM_START, programData.data(), programData.size());
		while (_PC - PROGRAM_START < programData.size()) {

			/* Debugging, checking registers */
			cycle();
			for (int i = 0; i < 16; i++) {
				std::cout << (i) << " " << +(_registers.read(i)) << " ";
			}
			std::cout << "Finished \n";

			/* End of debugging */

			/*for (int k = 0; k < 256; k++) {
				if (GetAsyncKeyState(k) & 0x8000) {
					std::cout << "Pressed!" << std::endl; break;
				}
			}*/
		}
	}

	std::string Chip8::decode(uint16_t ins) {
		int insType = ins >> 12;
		std::string type = "";
		std::cout << ((ins & 0xF000) >> 12) << " " << ((ins & 0xF00) >> 8) << " " << ((ins & 0xF0) >> 4) << " " << (ins & 0xF) << std::endl;
		switch (insType) {
		case 0:
			switch (ins & 0xF00) {
			case 0:
				if (ins & 0xF) {
					Instruction::OP_00EE(_PC, _stack);
				}
				else {
					Instruction::OP_00E0(_display);
				}
				break;
			default:
				std::cout << "SYS addr" << std::endl;
				assert(0);
			}
			break;
		case 1:
			Instruction::OP_1nnn(ins, _PC);
			break;
		case 2:
			Instruction::OP_2nnn(ins, _PC, _stack);
			break;
		case 3:
			Instruction::OP_3xkk(ins, _PC, _registers);
			break;
		case 4:
			Instruction::OP_4xkk(ins, _PC, _registers);
			break;
		case 5:
			Instruction::OP_5xy0(ins, _PC, _registers);
			break;
		case 6:
			Instruction::OP_6xkk(ins, _registers);
			break;
		case 7:
			Instruction::OP_7xkk(ins, _registers);
			break;
		case 8:
			switch (ins & 0xF) {
			case 0:
				Instruction::OP_8xy0(ins, _registers);
				break;
			case 4:
				Instruction::OP_8xy4(ins, _registers);
				break;
			case 5:
				Instruction::OP_8xy5(ins, _registers);
				break;
			case 7:
				Instruction::OP_8xy7(ins, _registers);
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
		case 0xA:
			Instruction::OP_Annn(ins, _registers);
			break;
		case 0xD:
			Instruction::OP_Dxyn(ins, _registers, _display, _memory);
			break;
		case 0xE:
			if ((ins & 0xF) == 0xE) {
				Instruction::OP_Ex9E(_PC, _registers);
			}
			else {
				Instruction::OP_ExA1(_PC, _registers);
			}
		case 0xF:
			switch ((ins & 0xF0) >> 4) {
			case 0:
				if ((ins & 0xF) == 0x7) {
					Instruction::OP_Fx07(ins, _registers, _delayTimer);
				}
				else if ((ins & 0xF) == 0xA) {

				}
				else {
					assert(0);
				}
			case 1:
				if ((ins & 0xF) == 0xE) {
					//Instruction::OP_Fx1E(ins, _registers);
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

	void Chip8::cycle() {
		uint16_t operationCode = _memory.read(_PC);

		std::cout << decode(operationCode) << " " << _PC << std::endl;
		_PC += 2;

		if (_delayTimer.read()) {
			_delayTimer.decrement();
		}
		if (_soundTimer.read()) {
			_soundTimer.decrement();
		}
		Sleep(167);
	}
};