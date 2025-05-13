#pragma once
#include <array>
#include <cstdint>

namespace chip8 {
	class Stack {
	public:
		Stack();
		~Stack();
		uint16_t top();
		uint16_t pop();
		void push(uint16_t&);

	private:
		std::array<uint16_t, 16> _stack;
		int8_t _pointer;
	};
}