#include "instruction.h"

#include <iostream>
#include <Windows.h>

namespace chip8 {
	// Instruction with unique first digit

	uint8_t Instruction::getVx(uint16_t& operationCode) {
		return (operationCode >> 8) & 0x0F;
	}

	uint8_t Instruction::getVy(uint16_t& operationCode) {
		return (operationCode >> 4) & 0x00F;
	}

	//void Instruction::OP_00E0(Display& display) {
	//	for (int i = 0; i < 32; i++) {
	//		for (int j = 0; j < 64; j++) {
	//			display.write(i, j, false);
	//		}
	//	}
	//}

	//void Instruction::OP_00EE(uint16_t& programCounter, Stack& stack) {
	//	programCounter = stack.pop(); 
	//}

	//void Instruction::OP_1nnn(uint16_t operationCode, uint16_t& programCounter) {
	//	programCounter = (operationCode & 0xFFF);
	//}

	//void Instruction::OP_2nnn(uint16_t operationCode, uint16_t& programCounter, Stack& stack) {
	//	stack.push(programCounter);
	//	programCounter = operationCode & 0xFFF;
	//}

	//void Instruction::OP_3xkk(uint16_t operationCode, uint16_t& programCounter, Registers& reg) {
	//	if (reg.read(getVx(operationCode)) == (operationCode & 0xFF)) {
	//		programCounter += 2;
	//	}
	//}

	//void Instruction::OP_4xkk(uint16_t operationCode, uint16_t& programCounter, Registers& reg) {
	//	if (reg.read(getVx(operationCode)) != (operationCode & 0xFF)) {
	//		programCounter += 2;
	//	}
	//}

	//void Instruction::OP_5xy0(uint16_t operationCode, uint16_t& programCounter, Registers& reg) {
	//	if (reg.read(getVx(operationCode)) == reg.read(getVy(operationCode))) {
	//		programCounter += 2;
	//	}
	//}

	//void Instruction::OP_6xkk(uint16_t operationCode, Registers& registers) {
	//	registers.write(getVx(operationCode), (uint8_t) (operationCode & 0xFF));
	//}

	//void Instruction::OP_7xkk(uint16_t operationCode, Registers& registers) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t result = (registers.read(Vx) + (operationCode & 0xFF));

	//	registers.write(Vx, result);
	//}

	//void Instruction::OP_9xy0(uint16_t operationCode, uint16_t& programCounter, Registers& registers) {
	//	if (registers.read(getVx(operationCode)) != registers.read(getVy(operationCode))) {
	//		programCounter += 2;
	//	}
	//}

	//void Instruction::OP_Annn(uint16_t operationCode, Registers& reg) {
	//	reg.iWrite(operationCode & 0xFFF);
	//}

	//void Instruction::OP_Bnnn(uint16_t operationCode, uint16_t& programCounter, Registers& reg) {
	//	uint8_t V0 = reg.read(0);
	//	programCounter = (operationCode & 0xFFF) + V0;
	//}

	//void Instruction::OP_Cxkk(uint16_t operationCode, Registers& reg) {
	//	uint8_t result = (operationCode & 0xFF) & (std::rand() % 256);
	//	reg.write(getVx(operationCode), result);
	//}

	//void Instruction::OP_Dxyn(uint16_t operationCode, Registers& reg, Display& display, Memory& memory) {
	//	uint8_t x = reg.read(getVx(operationCode));
	//	uint8_t y = reg.read(getVy(operationCode));

	//	reg.write(0xF, (uint8_t) 0);

	//	uint8_t n = operationCode & 0xF;
	//	uint16_t address = reg.iRead();

	//	for (int i = 0; i < n; ++i) {
	//		uint8_t spriteByte = memory.readByte(address + i);
	//		for (int j = 0; j < 8; ++j) {
	//			//std::cout << (x + i) << " " << (y + j) << std::endl;
	//			bool result = (spriteByte >> (7-j)) & 1;
	//			if (result) {
	//				int vx = (x & 63) + j;
	//				int vy = (y & 31) + i;
	//				if ((vx < 64) && (vy < 32)) {
	//					bool displayPixel = display.read(vy, vx);
	//					bool xorResult = result ^ displayPixel;

	//					if (!xorResult && displayPixel) {
	//						reg.write(0xF, (uint8_t)1);
	//					}
	//					display.write(vy, vx, xorResult);
	//				}
	//			}
	//		}
	//	}
	//}

	///* 8 type instructions */

	//void Instruction::OP_8xy0(uint16_t operationCode, Registers& reg) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t Vy = getVy(operationCode);

	//	reg.write(Vx, reg.read(Vy));
	//}

	//void Instruction::OP_8xy1(uint16_t operationCode, Registers& reg) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t Vy = getVy(operationCode);

	//	reg.write(Vx, (uint8_t) (reg.read(Vx) | reg.read(Vy)));
	//	reg.write(0xF, 0);
	//}

	//void Instruction::OP_8xy2(uint16_t operationCode, Registers& reg) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t Vy = getVy(operationCode);

	//	reg.write(Vx, (uint8_t) (reg.read(Vx) & reg.read(Vy)));
	//	reg.write(0xF, 0);
	//}

	//void Instruction::OP_8xy3(uint16_t operationCode, Registers& reg) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t Vy = getVy(operationCode);

	//	reg.write(Vx, (uint8_t) (reg.read(Vx) ^ reg.read(Vy)));
	//	reg.write(0xF, 0);
	//}

	//void Instruction::OP_8xy4(uint16_t operationCode, Registers& reg) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t Vy = getVy(operationCode);
	//	uint16_t result = reg.read(Vx) + reg.read(Vy);

	//	reg.write(Vx, (uint8_t) result & 0xFF);
	//	if (result > 0xFF) {
	//		reg.write(0xF, 1);
	//	}
	//	else {
	//		reg.write(0xF, 0);
	//	}

	//}

	//void Instruction::OP_8xy5(uint16_t operationCode, Registers& reg) {
	//	uint8_t x = getVx(operationCode);
	//	uint8_t Vx = reg.read(x);
	//	uint8_t Vy = reg.read(getVy(operationCode));
	//	
	//	reg.write(x, (uint8_t) (Vx - Vy));
	//	reg.write(0xF, (bool)(Vx >= Vy));
	//}

	//void Instruction::OP_8xy6(uint16_t operationCode, Registers& reg) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t aux = reg.read(getVy(operationCode));

	//	// Shifting quirks off
	//	// uint8_t aux2 = reg.read(Vx);
	//	
	//	reg.write(Vx, (uint8_t) (aux >> 1));
	//	reg.write(0xF, (bool)(aux & 1));
	//}

	//void Instruction::OP_8xy7(uint16_t operationCode, Registers& reg) {
	//	uint8_t x = getVx(operationCode);
	//	uint8_t Vx = reg.read(x);
	//	uint8_t Vy = reg.read(getVy(operationCode));

	//	reg.write(x, (uint8_t) (Vy - Vx));
	//	reg.write(0xF, (Vy >= Vx) ? 0x01 : 0x00);
	//}

	//void Instruction::OP_8xyE(uint16_t operationCode, Registers& reg) {
	//	uint8_t Vx = getVx(operationCode);
	//	uint8_t aux = reg.read(getVy(operationCode));
	//	uint8_t result = aux << 1;

	//	// Shifting quirks off
	//	// uint8_t aux2 = reg.read(Vx);
	//	
	//	reg.write(Vx, result);
	//	reg.write(0xF, (uint8_t)((aux & 0x80) >> 7));
	//}

	///* E type instructions */

	//void Instruction::OP_Ex9E(uint16_t operationCode, uint16_t& programCounter, Registers& reg, Keypad& keypad) {
	//	uint8_t key = reg.read(getVx(operationCode));
	//	if (keypad.read(key)) {
	//		programCounter += 2;
	//	}
	//}

	//void Instruction::OP_ExA1(uint16_t operationCode, uint16_t& programCounter, Registers& reg, Keypad& keypad) {
	//	uint8_t key = reg.read(getVx(operationCode));
	//	if (!keypad.read(key)) {
	//		programCounter += 2;
	//	}
	//}

	///* F type instructions */

	//void Instruction::OP_Fx07(uint16_t operationCode, Registers& reg, Timer& delay) {
	//	reg.write(getVx(operationCode), delay.read());
	//}

	//void Instruction::OP_Fx0A(uint16_t operationCode, uint16_t& programCounter, Registers& reg, Keypad& keypad) {
	//	uint8_t Vx = getVx(operationCode);
	//	bool flag = false;
	//	uint8_t key = 0;
	//	for (int i = 0; i < 16; i++) {
	//		if (keypad.read(i)) {
	//			flag = true; key = i;
	//			break;
	//		}
	//	}
	//	if (!flag) {
	//		programCounter -= 2;
	//	}
	//	else {
	//		reg.write(Vx, key);
	//	}
	//}

	//void Instruction::OP_Fx15(uint16_t operationCode, Registers& reg, Timer& delay) {
	//	uint8_t Vx = getVx(operationCode);
	//	delay.set(reg.read(Vx));
	//}

	//void Instruction::OP_Fx18(uint16_t operationCode, Registers& reg, Timer& sound) {
	//	uint8_t Vx = getVx(operationCode);
	//	sound.set(reg.read(Vx));
	//}

	//void Instruction::OP_Fx1E(uint16_t operationCode, Registers& reg) {
	//	uint16_t result = reg.iRead() + reg.read(getVx(operationCode));
	//	reg.iWrite(result);
	//}

	//void Instruction::OP_Fx29(uint16_t operationCode, Registers& reg, Memory& mem) {
	//	uint8_t digit = reg.read(getVx(operationCode));
	//	reg.iWrite(0x050 + 5 * digit);
	//}


	//void Instruction::OP_Fx33(uint16_t operationCode, Registers& reg, Memory& mem) {
	//	uint8_t Vx = reg.read(getVx(operationCode));
	//	uint16_t address = reg.iRead();
	//	mem.write(address + 2, Vx % 10); Vx /= 10;
	//	mem.write(address + 1, Vx % 10); Vx /= 10;
	//	mem.write(address, Vx);
	//}

	//void Instruction::OP_Fx55(uint16_t operationCode, Registers& reg, Memory& mem) {
	//	uint16_t address = reg.iRead();
	//	uint8_t x = getVx(operationCode);
	//	for (uint8_t i = 0; i <= x; ++i) {
	//		mem.write(address + i, reg.read(i));
	//	}

	//	reg.iWrite(address + x + 1);
	//}

	//void Instruction::OP_Fx65(uint16_t operationCode, Registers& reg, Memory& mem) {
	//	uint16_t address = reg.iRead();
	//	uint8_t x = getVx(operationCode);
	//	for (uint8_t i = 0; i <= x; ++i) {
	//		reg.write(i, mem.readByte(address + i));
	//	}

	//	reg.iWrite(address + x + 1);
	//}

	/* Implementación con interfaz uniforme */

	void Instruction::OP_00E0(uint16_t operationCode, Chip8& chip) {
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 64; j++) {
				chip._display.write(i, j, false);
			}
		}
	}
	void Instruction::OP_00EE(uint16_t operationCode, Chip8& chip) {
		chip._PC = chip._stack.pop();
	}

	// "First digit is unique" instructions

	void Instruction::OP_1nnn(uint16_t operationCode, Chip8& chip) {
		chip._PC= (operationCode & 0xFFF);
	}

	void Instruction::OP_2nnn(uint16_t operationCode, Chip8& chip) {
		chip._stack.push(chip._PC);
		chip._PC = operationCode & 0xFFF;
	}

	void Instruction::OP_3xkk(uint16_t operationCode, Chip8& chip) {
		if (chip._registers.read(getVx(operationCode)) == (operationCode & 0xFF)) {
			chip._PC += 2;
		}
	}
	void Instruction::OP_4xkk(uint16_t operationCode, Chip8& chip) {
		if (chip._registers.read(getVx(operationCode)) != (operationCode & 0xFF)) {
			chip._PC += 2;
		}
	}

	void Instruction::OP_5xy0(uint16_t operationCode, Chip8& chip) {
		if (chip._registers.read(getVx(operationCode)) == chip._registers.read(getVy(operationCode))) {
			chip._PC += 2;
		}
	}

	void Instruction::OP_6xkk(uint16_t operationCode, Chip8& chip) {
		chip._registers.write(getVx(operationCode), (uint8_t) (operationCode & 0xFF));
	}
	void Instruction::OP_7xkk(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t result = (chip._registers.read(Vx) + (operationCode & 0xFF));

		chip._registers.write(Vx, result);
	}

	void Instruction::OP_9xy0(uint16_t operationCode, Chip8& chip) {
		if (chip._registers.read(getVx(operationCode)) != chip._registers.read(getVy(operationCode))) {
			chip._PC += 2;
		}
	}

	void Instruction::OP_Annn(uint16_t operationCode, Chip8& chip) {
		chip._registers.iWrite(operationCode & 0xFFF);
	}

	void Instruction::OP_Bnnn(uint16_t operationCode, Chip8& chip) {
		uint8_t V0 = chip._registers.read(0);
		chip._PC = (operationCode & 0xFFF) + V0;
	}

	void Instruction::OP_Cxkk(uint16_t operationCode, Chip8& chip) {
		uint8_t result = (operationCode & 0xFF) & (std::rand() % 256);
		chip._registers.write(getVx(operationCode), result);
	}
	void Instruction::OP_Dxyn(uint16_t operationCode, Chip8& chip) {
		uint8_t x = chip._registers.read(getVx(operationCode));
		uint8_t y = chip._registers.read(getVy(operationCode));

		chip._registers.write(0xF, (uint8_t)0);

		uint8_t n = operationCode & 0xF;
		uint16_t address = chip._registers.iRead();

		for (int i = 0; i < n; ++i) {
			uint8_t spriteByte = chip._memory.readByte(address + i);
			for (int j = 0; j < 8; ++j) {
				//std::cout << (x + i) << " " << (y + j) << std::endl;
				bool result = (spriteByte >> (7 - j)) & 1;
				if (result) {
					int vx = (x & 63) + j;
					int vy = (y & 31) + i;
					if ((vx < 64) && (vy < 32)) {
						bool displayPixel = chip._display.read(vy, vx);
						bool xorResult = result ^ displayPixel;

						if (!xorResult && displayPixel) {
							chip._registers.write(0xF, (uint8_t)1);
						}
						chip._display.write(vy, vx, xorResult);
					}
				}
			}
		}
	}

	// "First digit is 8" instructions

	void Instruction::OP_8xy0(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t Vy = getVy(operationCode);

		chip._registers.write(Vx, chip._registers.read(Vy));
	}

	void Instruction::OP_8xy1(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t Vy = getVy(operationCode);

		chip._registers.write(Vx, (uint8_t)(chip._registers.read(Vx) | chip._registers.read(Vy)));
		chip._registers.write(0xF, 0);
	}

	void Instruction::OP_8xy2(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t Vy = getVy(operationCode);

		chip._registers.write(Vx, (uint8_t)(chip._registers.read(Vx) & chip._registers.read(Vy)));
		chip._registers.write(0xF, 0);
	}

	void Instruction::OP_8xy3(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t Vy = getVy(operationCode);

		chip._registers.write(Vx, (uint8_t)(chip._registers.read(Vx) ^ chip._registers.read(Vy)));
		chip._registers.write(0xF, 0);
	}

	void Instruction::OP_8xy4(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t Vy = getVy(operationCode);
		uint16_t result = chip._registers.read(Vx) + chip._registers.read(Vy);

		chip._registers.write(Vx, (uint8_t)result & 0xFF);
		if (result > 0xFF) {
			chip._registers.write(0xF, 1);
		}
		else {
			chip._registers.write(0xF, 0);
		}
	}

	void Instruction::OP_8xy5(uint16_t operationCode, Chip8& chip) {
		uint8_t x = getVx(operationCode);
		uint8_t Vx = chip._registers.read(x);
		uint8_t Vy = chip._registers.read(getVy(operationCode));

		chip._registers.write(x, (uint8_t)(Vx - Vy));
		chip._registers.write(0xF, (bool)(Vx >= Vy));
	}

	void Instruction::OP_8xy6(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t aux = chip._registers.read(getVy(operationCode));

		chip._registers.write(Vx, (uint8_t)(aux >> 1));
		chip._registers.write(0xF, (bool)(aux & 1));
	}

	void Instruction::OP_8xy7(uint16_t operationCode, Chip8& chip) {
		uint8_t x = getVx(operationCode);
		uint8_t Vx = chip._registers.read(x);
		uint8_t Vy = chip._registers.read(getVy(operationCode));

		chip._registers.write(x, (uint8_t)(Vy - Vx));
		chip._registers.write(0xF, (bool)(Vx < Vy));
	}
	void Instruction::OP_8xyE(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		uint8_t aux = chip._registers.read(getVy(operationCode));
		uint8_t result = aux << 1;

		// Shifting quirks off
		// uint8_t aux2 = reg.read(Vx);

		chip._registers.write(Vx, result);
		chip._registers.write(0xF, (uint8_t)((aux & 0x80) >> 7));
	}

	/* E instructions */

	void Instruction::OP_Ex9E(uint16_t operationCode, Chip8& chip) {
		uint8_t key = chip._registers.read(getVx(operationCode));
		if (chip._keypad.read(key)) {
			chip._PC += 2;
		}
	}

	void Instruction::OP_ExA1(uint16_t operationCode, Chip8& chip) {
		uint8_t key = chip._registers.read(getVx(operationCode));
		if (!chip._keypad.read(key)) {
			chip._PC += 2;
		}
	}

	/* F instructions */

	void Instruction::OP_Fx07(uint16_t operationCode, Chip8& chip) {
		chip._registers.write(getVx(operationCode), chip._delayTimer.read());
	}

	void Instruction::OP_Fx0A(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		bool flag = false;
		uint8_t key = 0;
		for (int i = 0; i < 16; i++) {
			if (chip._keypad.read(i)) {
				flag = true; key = i;
				break;
			}
		}
		if (!flag) {
			chip._PC -= 2;
		}
		else {
			chip._registers.write(Vx, key);
		}
	}
	
	void Instruction::OP_Fx15(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		chip._delayTimer.set(chip._registers.read(Vx));
	}

	void Instruction::OP_Fx18(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = getVx(operationCode);
		chip._soundTimer.set(chip._registers.read(Vx));
	}

	void Instruction::OP_Fx1E(uint16_t operationCode, Chip8& chip) {
		uint16_t result = chip._registers.iRead() + chip._registers.read(getVx(operationCode));
		chip._registers.iWrite(result);
	}

	void Instruction::OP_Fx29(uint16_t operationCode, Chip8& chip) {
		uint8_t digit = chip._registers.read(getVx(operationCode));
		chip._registers.iWrite(0x050 + 5 * digit);
	}
	void Instruction::OP_Fx33(uint16_t operationCode, Chip8& chip) {
		uint8_t Vx = chip._registers.read(getVx(operationCode));
		uint16_t address = chip._registers.iRead();
		chip._memory.write(address + 2, Vx % 10); Vx /= 10;
		chip._memory.write(address + 1, Vx % 10); Vx /= 10;
		chip._memory.write(address, Vx);
	}

	void Instruction::OP_Fx55(uint16_t operationCode, Chip8& chip) {
		uint16_t address = chip._registers.iRead();
		uint8_t x = getVx(operationCode);
		for (uint8_t i = 0; i <= x; ++i) {
			chip._memory.write(address + i, chip._registers.read(i));
		}

		chip._registers.iWrite(address + x + 1);
	}

	void Instruction::OP_Fx65(uint16_t operationCode, Chip8& chip) {
		uint16_t address = chip._registers.iRead();
		uint8_t x = getVx(operationCode);
		for (uint8_t i = 0; i <= x; ++i) {
			chip._registers.write(i, chip._memory.readByte(address + i));
		}

		chip._registers.iWrite(address + x + 1);
	}
}