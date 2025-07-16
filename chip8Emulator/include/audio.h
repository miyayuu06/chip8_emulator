#pragma once
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

namespace chip8 {
	class Audio {
	public:
		Audio();
		~Audio();
		short SineWave(int timeInSample, double freq, double amp);
		static void callback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount);
		void update(uint8_t timer);
	private:
		short _buffer[44100];
		int _BUFFER_SIZE = 44100;
		SDL_AudioStream* _stream = NULL;
	};
}