#include "graphics.h"
#include <iostream>
#define SDL_MAIN_HANDLED

using namespace chip8;

Graphics::Graphics() {
	window = SDL_CreateWindow("Chip-8 Display", 1280, 640, 0);
	renderer = SDL_CreateRenderer(window, NULL);
	height = 32;
	width = 64;
	mode = false;
}

Graphics::~Graphics() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::setSize(int x, int y) {
	height = x;
	width = y;
	mode = (height == 64);
}

void Graphics::draw(Display& display) {
	SDL_SetRenderDrawColor(renderer, 60, 65, 44, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 168, 198, 78, 255);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (display.read(i, j)) {
				float size = mode ? 10 : 20;
				pixel = { (float)size * j, (float)size * i, size, size};
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
