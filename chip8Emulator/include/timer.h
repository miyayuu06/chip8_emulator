#pragma once
#include <cstdint>

namespace chip8 {
	class Timer {
	public:
		Timer();
		~Timer();
		void increment();
		void decrement();
		void set(uint8_t time);
		uint8_t read();
	private:
		uint8_t value;
	};
}