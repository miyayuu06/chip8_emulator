#pragma once
#include <cstdint>
#include <array>
#include <vector>

namespace chip8 {

	class Memory {
	public:
		Memory();
		~Memory();
		uint16_t read(uint16_t address);
		void write(uint16_t address, uint8_t data);
		void write(uint32_t address, const uint8_t* data, size_t dataSizeInBytes);

	private:
		std::array<uint8_t, 4096> _space;
	};
}