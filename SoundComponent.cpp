
// C++ Standard Libraries
#include <iostream>

// This Class header
#include "SoundComponent.h"


SoundComponent::SoundComponent(std::string path) 
{
    if (SDL_LoadWAV(path.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr) {
        std::cerr << "sound loading error: " << SDL_GetError() << std::endl;
    }
}


SoundComponent::~SoundComponent() 
{
    SDL_FreeWAV(m_waveStart);
    SDL_CloseAudioDevice(m_device);
}


void SoundComponent::setupDevice()
{
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, 0);

    if (0 == m_device) {
        std::cerr << "sound device error: " << SDL_GetError() << std::endl;
    }
}


void SoundComponent::playSound() 
{
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
    SDL_PauseAudioDevice(m_device, 0);
}


void SoundComponent::stopSound() 
{
    SDL_PauseAudioDevice(m_device, 1);
}

