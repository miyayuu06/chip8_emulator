#include "timer.h"

namespace chip8 {
	Timer::Timer() {
	}

	Timer::~Timer() {
	}

	void Timer::increment() {
		value++;
	}

	void Timer::decrement() {
		value--;
	}

	void Timer::set(uint8_t time) {
		value = time;
	}

	uint8_t Timer::read() {
		return value;
	}
}