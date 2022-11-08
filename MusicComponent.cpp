
// C++ Standard Libraries
#include <iostream>

// Class Headers
#include "AssetManager.h"

// This Class header
#include "MusicComponent.h"


MusicComponent::MusicComponent(std::string path, int volume)
	: m_volume  { volume }
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		std::cout << "Audio library not working:" << Mix_GetError() << std::endl;;
	}

	m_music = AssetManager::getInstance().loadMusic(path);
	setVolume(volume);

	// std::cout << "\t Audio component created" << std::endl;
}


MusicComponent::~MusicComponent()
{
	{
		Mix_FreeMusic(m_music);
	}
}


void MusicComponent::setVolume(int volume)
{
	Mix_VolumeMusic(volume);
}


void MusicComponent::playMusic(int loops)
{
	Mix_PlayMusic(m_music, loops);
}


void MusicComponent::pauseAudio()
{
	Mix_PauseMusic();
}


