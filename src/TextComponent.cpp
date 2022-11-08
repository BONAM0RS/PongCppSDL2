
// C++ Standard Libraries
#include <iostream>

// Class Headers
#include "AssetManager.h"
#include "ObjectManager.h"

// This Class header
#include "TextComponent.h"


TextComponent::TextComponent(const std::string& fontpath, int ptsize, const std::string& text)
{
	m_text = text;
	setFont(fontpath, ptsize);
}


TextComponent::~TextComponent()
{
	SDL_DestroyTexture(m_texture);
	TTF_CloseFont(m_font);
}


void TextComponent::setFont(const std::string &fontpath, int ptsize)
{
	m_font = AssetManager::getInstance().loadTextFont(fontpath, ptsize);
	setTexture();
}


void TextComponent::setText(const std::string &text)
{
	m_text = text;
	setTexture();
}


void TextComponent::setTexture()
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, m_text.c_str(), { 255,255,255 });

	if (surface == NULL)
	{
		std::cout << "Surface:" << SDL_GetError() << std::endl;
	}

	SDL_Renderer* renderer = ObjectManager::getInstance().getRenderer();

	m_texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (m_texture == NULL)
	{
		std::cout << "Could not load texture" << std::endl;
	}

	SDL_FreeSurface(surface);
}


std::string TextComponent::getText() const
{
	return m_text;
}


SDL_Texture* TextComponent::getTexture() const
{
	return m_texture;
}

