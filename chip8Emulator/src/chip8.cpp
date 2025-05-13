#include "chip8.h"
#include <filesystem>
#include <Windows.h>

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
			uint16_t operationCode = _memory.read(_PC);

			std::cout << Instruction::decode(operationCode, _PC, _registers, _display, _delayTimer, _soundTimer, _stack, _memory) << " " << _PC << std::endl;
			_PC += 2;

			/* Debugging, checking registers */

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
	void Chip8::cycle() {
		if (_delayTimer.read()) {
			_delayTimer.decrement();
		}
		if (_soundTimer.read()) {
			_soundTimer.decrement();
		}
		Sleep(167);
	}
};