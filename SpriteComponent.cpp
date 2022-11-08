
// C++ Standard Libraries
#include <iostream>

// Class Headers
#include "AssetManager.h"

// This Class header
#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(std::string path)	
{ 
	setTexture(path);

	// std::cout << "\t Sprite component created" << std::endl;
}


SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(m_texture);

	// std::cout << "\t Sprite component destroyed" << std::endl;
}


void SpriteComponent::setTexture(std::string path)
{
	m_texture = AssetManager::getInstance().loadSpriteTexture(path);
}


SDL_Texture* SpriteComponent::getTexture() 
{ 
	return m_texture;
}

