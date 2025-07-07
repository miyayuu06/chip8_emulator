#include "graphics.h"
#include <iostream>
#define SDL_MAIN_HANDLED

using namespace chip8;

Graphics::Graphics() {
	window = SDL_CreateWindow("Chip-8 Display", 1280, 640, 0);
	renderer = SDL_CreateRenderer(window, NULL);
}

Graphics::~Graphics() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::draw(Display display) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 64; j++) {
			if (display.read(i, j)) {
				pixel = { (float)20 * j, (float)20 * i, 20, 20 };
				SDL_RenderFillRect(renderer, &pixel);
			}
		}
	}

	SDL_RenderPresent(renderer);
}

bool Graphics::update(Keypad& keypad) {
	bool quit = false;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		std::cout << event.type << std::endl;
		switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
			for (int i = 0; i < 16; i++) {
				if (event.key.key == _KEYMAPPING[i]) {
					keypad.write(i, true);
				}
			} 
			break;
		case SDL_EVENT_KEY_UP:
			for (int i = 0; i < 16; i++) {
				if (event.key.key == _KEYMAPPING[i]) {
					keypad.write(i, false);
				}
			}
			break;
		case SDL_EVENT_QUIT:
			quit = true;
			break;
		}
	}
	return quit;
}
