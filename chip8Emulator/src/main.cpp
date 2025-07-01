// InstructionEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "chip8.h"


using namespace chip8;

int main()
{
    Chip8 chip8;
    //int programDataSize = chip8.load_rom("C:/Users/yunaf/Desktop/Tetris.ch8");
    int programDataSize = chip8.load_rom("C:/Users/yunaf/Desktop/1-chip8-logo.ch8");
    //int programDataSize = chip8.load_rom("C:/Users/yunaf/Desktop/3-corax+.ch8");
    //int programDataSize = chip8.load_rom("C:/Users/yunaf/Desktop/test_opcode.ch8");
    chip8.program(programDataSize);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
