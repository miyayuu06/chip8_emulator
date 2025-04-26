#include "chip8.h"
#include <filesystem>

namespace chip8 {
	Chip8::Chip8() {
		_keypad = new uint8_t[16];
		_stack = new uint16_t[16];
			
		/*_delayTimer = Timer::Timer();
		_soundTimer = Timer::Timer(); */

		_opcode = 0x00;

		_PC = Chip8::PROGRAM_START;
	}

	Chip8::~Chip8() {
		delete[] _keypad;
		delete[] _stack;
	}

	void Chip8::rom(std::string path) {
		std::ifstream rf(path, std::ios::out | std::ios::binary);
		if (!rf) {
			std::cout << "Can not access file, sowwy!" << std::endl;
			return;
		}
		int fileSize = std::filesystem::file_size(path);
		std::vector<uint8_t> programData(fileSize);
		rf.read((char*)programData.data(), fileSize);
		rf.close();
		_memory.write(0x200, programData.data(), programData.size());
		for (int i = 0x200; i < 4096; i++) {
			std::cout << _memory.read(i);
		}
	}

};