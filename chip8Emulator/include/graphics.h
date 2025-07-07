#pragma once
#include "display.h";
#include "keypad.h"

#include <SDL3/SDL.h>

namespace chip8 {
	class Graphics {
	public:
		Graphics();
		~Graphics();
		void draw(Display display);
		bool update(Keypad& keypad);
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_FRect pixel;

		const std::array<SDL_Keycode, 16> _KEYMAPPING = {
			SDLK_X, SDLK_1, SDLK_2, SDLK_3,
			SDLK_Q, SDLK_W, SDLK_E, SDLK_A,
			SDLK_S, SDLK_D, SDLK_Z, SDLK_C,
			SDLK_4, SDLK_R, SDLK_F, SDLK_V
		};
	};
};