#include "stack.h"

namespace chip8 {
	Stack::Stack() {
		_pointer = -1;
	}

	Stack::~Stack() {
	}

	uint16_t Stack::top() {
		return _stack[_pointer];
	}

	uint16_t Stack::pop() {
		if (_pointer) {
			_pointer--;
			return _stack[_pointer + 1];
		}
		return _stack[_pointer];
	}

	void Stack:: push(uint16_t& programCounter) {
		_pointer++;
		_stack[_pointer] = programCounter;
	}
}