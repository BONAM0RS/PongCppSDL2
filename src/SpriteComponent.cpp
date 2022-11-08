
// C++ Standard Libraries
#include <iostream>

// Class Headers
#include "AssetManager.h"

// This Class header
#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(const std::string &path)
{ 
	setTexture(path);

	// std::cout << "\t Sprite component created" << std::endl;
}


SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(m_texture);

	// std::cout << "\t Sprite component destroyed" << std::endl;
}


void SpriteComponent::setTexture(const std::string &path)
{
	m_texture = AssetManager::getInstance().loadSpriteTexture(path);
}


SDL_Texture* SpriteComponent::getTexture() const
{ 
	return m_texture;
}

