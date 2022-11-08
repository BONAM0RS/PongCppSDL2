
#pragma once

// C++ Standard Libraries
#include <string>

// SDL Libraries
//

// Class Headers
//


class SpriteComponent {

public:
	SpriteComponent(const std::string &path);
	~SpriteComponent();

	void setTexture(const std::string &path);

	SDL_Texture* getTexture() const;

private:
	SDL_Texture* m_texture = nullptr;
};