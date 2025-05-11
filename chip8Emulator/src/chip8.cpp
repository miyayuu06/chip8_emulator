#include "chip8.h"
#include <filesystem>

namespace chip8 {
	Chip8::Chip8() {
		_keypad = new uint8_t[16];
		_stack = new uint16_t[16];
			
		/*_delayTimer = Timer::Timer();
		_soundTimer = Timer::Timer(); */

		_PC = Chip8::PROGRAM_START;
	}

	Chip8::~Chip8() {
		delete[] _keypad;
		delete[] _stack;
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
			uint16_t previousPC = _PC;
			std::cout << Instruction::decode(operationCode, _PC, _registers, _display) << " " << +_PC << std::endl;
			
			/* Debugging, checking registers */

			for (int i = 0; i < 16; i++) {
				std::cout << (i) << " " << +(_registers.read(i)) << " ";
			}
			std::cout  << "Finished \n";

			/* End of debugging */
			if (previousPC == _PC) {
				_PC += 2;
			}
		}
	}

};