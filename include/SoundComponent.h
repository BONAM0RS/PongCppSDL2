
#pragma once

// C++ Standard Libraries
#include <string>

// SDL Libraries
#include <SDL.h>

// Class Headers
//

class SoundComponent {

public:
	SoundComponent(std::string path);
	~SoundComponent();

	void playSound();
	void stopSound();

private:
	void setupDevice();

	SDL_AudioDeviceID m_device;

	SDL_AudioSpec m_audioSpec;
	Uint8* m_waveStart;
	Uint32 m_waveLength;
};