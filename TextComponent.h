
#pragma once


// C++ Standard Libraries
#include <string>

// SDL Libraries
#include <SDL.h>
#include <SDL_ttf.h>

// Class Headers
//#include "Object.h"


class TextComponent {

public:
	TextComponent(const std::string &fontpath, int ptsize = 10, const std::string &text = {});
    ~TextComponent();

	void setFont(const std::string &fontpath, int ptsize = 10);
	void setText(std::string text);

	std::string getText();
	SDL_Texture* getTexture();

private:
	void setTexture();

	std::string m_text;

	TTF_Font* m_font = nullptr;
	SDL_Texture* m_texture = nullptr;
};

