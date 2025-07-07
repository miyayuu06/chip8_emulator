#include "stack.h"
#include <cassert>

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
		assert(_pointer > 0);
		_pointer--;
		return _stack[_pointer];
	}

	void Stack:: push(uint16_t& programCounter) {
		assert(_pointer < 15);
		_stack[_pointer] = programCounter;
		_pointer++;
	}
}