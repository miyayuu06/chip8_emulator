#include "audio.h"
#include <cmath>
#include <iostream>

namespace chip8 {
    int pos;
    Audio::Audio() {
        for (int i = 0; i < 44100; i++) {
            _buffer[i] = Audio::SineWave(i, 350.0f, 0.9f);
            //std::cout << i << " " << buffer[i] << std::endl;
        }

        SDL_Init(SDL_INIT_AUDIO);

        SDL_AudioSpec spec;
        spec.format = SDL_AUDIO_S16;
        spec.channels = 1;
        spec.freq = 44100;
        pos = 0;

        _stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, Audio::callback, &_buffer);

    }

    Audio::~Audio() {
        SDL_DestroyAudioStream(_stream);
    }

    short Audio::SineWave(int timeInSample, double freq, double amp) {
        double samplesPerRepetition = 44100 / freq;
        double cycles = timeInSample / samplesPerRepetition;
        double rad = 2 * acos(-1) * cycles;
        short amplitude = 32767 * amp;
        short result = amplitude * sin(rad);
        return result;
    };

    void Audio::callback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount) {
        short* auxiliary = static_cast<short*>(userdata);
        auxiliary += pos;
        if (pos + additional_amount >= 44100) {
            int excess = (pos + additional_amount) % 44100;
            if (!SDL_PutAudioStreamData(stream, auxiliary, additional_amount - excess)) {
                std::cout << "SDL_OpenAudioDevice error1: " << SDL_GetError() << "\n";
                return;
            }
            if (!SDL_PutAudioStreamData(stream, userdata, excess)) {
                std::cout << "SDL_OpenAudioDevice error2: " << SDL_GetError() << "\n";
                return;
            }
            pos = excess;
        }
        else {
            if (!SDL_PutAudioStreamData(stream, auxiliary, additional_amount)) {
                std::cout << "SDL_OpenAudioDevice error3: " << SDL_GetError() << "\n";
                return;
            }
            pos += additional_amount;
        }
    }

    void Audio::update(uint8_t timer) {
        if (timer) {
            SDL_ResumeAudioStreamDevice(_stream);
        }
        else {
            SDL_PauseAudioStreamDevice(_stream);
        }
    }
}