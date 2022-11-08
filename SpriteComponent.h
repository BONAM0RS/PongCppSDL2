
#pragma once

// C++ Standard Libraries
#include <string>

// SDL Libraries
//

// Class Headers
//


class SpriteComponent {

public:
	SpriteComponent(std::string path);
	~SpriteComponent();

	void setTexture(std::string path);

	SDL_Texture* getTexture();

private:
	SDL_Texture* m_texture = nullptr;
};