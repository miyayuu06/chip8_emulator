// InstructionEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "chip8.h"


using namespace chip8;

int main()
{

    std::cout << "Welcome to the Chip-8 emulator!\n\n\n";

    Chip8 chip8;
    int programDataSize = 0;

    while (!programDataSize) {
        std::string programNameLink;
        std::cout << "Introduce valid program: ";
        std::cin >> programNameLink;
        std::cout << std::endl;

        programDataSize = chip8.load_rom(programNameLink);

    }

    std::cout << "ROM Loading succesful!\n";

    chip8.program(programDataSize);

}
