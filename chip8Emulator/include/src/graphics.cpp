#include "graphics.h"
#include <iostream>
#define SDL_MAIN_HANDLED

using namespace chip8;

Graphics::Graphics() {
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (!SDL_CreateWindowAndRenderer("Chip8 Display", 1280, 640, SDL_WINDOW_OPENGL, &window, &renderer)) {
		std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
	}
	height = 32;
	width = 64;
	mode = false;
	SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
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
