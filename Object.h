
#pragma once

// C++ Standard Libraries
#include <string>
#include <memory>

// Class Headers
#include "LayerPriority.h"
#include "RectComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "MusicComponent.h"
#include "SoundComponent.h"


class Object {

public:
	Object(std::string name);
	~Object();

	void addRectComponent(int xPos = 0, int yPos = 0, int wSize = 0, int hSize = 0);
	void addSpriteComponent(std::string path);
	void addTextComponent(const std::string& fontpath, int ptsize = 10, const std::string& text = " ");
	void addMusicComponent(std::string path, int volume = 0);
	void addSoundComponent(std::string path);

	void setLayerPriority(LayerPriority priority);

	RectComponent* getRectComponent();
	SpriteComponent* getSpriteComponent();
	TextComponent* getTextComponent();
	MusicComponent* getMusicComponent();
	SoundComponent* getSoundComponent();

	std::string getName();
	bool getGraphicState();
	LayerPriority getLayerPriority();

protected:
	RectComponent* m_rectComponent = nullptr;
	SpriteComponent* m_spriteComponent = nullptr;
	TextComponent* m_textComponent = nullptr;
	MusicComponent* m_musicComponent = nullptr;
	SoundComponent* m_soundComponent = nullptr;

	std::string m_name;
	bool m_isGraphic;

	LayerPriority m_layerPriority;
};

