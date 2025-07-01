#include "stack.h"

namespace chip8 {
	Stack::Stack() {
		_pointer = 0;
	}

	Stack::~Stack() {
	}

	uint16_t Stack::top() {
		return _stack[_pointer];
	}

	uint16_t Stack::pop() {
		_pointer--;
		return _stack[_pointer];
	}

	void Stack:: push(uint16_t& programCounter) {
		_stack[_pointer] = programCounter;
		_pointer++;
	}
}