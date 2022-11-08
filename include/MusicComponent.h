
#pragma once

// C++ Standard Libraries
#include <string>

// SDL Libraries
#include <SDL_mixer.h>


class MusicComponent {

public:
	MusicComponent(const std::string &path, int volume);
	~MusicComponent();

	// A range of 0 to 128
	void setVolume(int volume);

	// 0 = play once, -1 = play repeat
	void playMusic(int loops); 

	void pauseAudio();

private:
	Mix_Music* m_music = nullptr;

	int m_volume;
};