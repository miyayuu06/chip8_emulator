#pragma once
#include "display.h";

#include <SDL3/SDL.h>

namespace chip8 {
	class Graphics {
	public:
		Graphics();
		~Graphics();
		void draw(Display display);
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_FRect pixel;
	};
};