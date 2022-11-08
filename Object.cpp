
// C++ Standard Libraries
#include <iostream>

// This Class header
#include "Object.h"


Object::Object(std::string name)
	: m_name          { name  },
	  m_isGraphic     { false },
	  m_layerPriority { LayerPriority::BACKGROUND }
{ 
	// std::cout << "\t The Object '" << m_name << "' created" << std::endl;
}


Object::~Object()
{
	if (m_rectComponent != nullptr)
	{
		delete m_rectComponent;
		// std::cout << "\t The Object '" << m_name << "' deleted Rect compoment" << std::endl;
	}

	if (m_spriteComponent != nullptr)
	{
		delete m_spriteComponent;
		// std::cout << "\t The Object '" << m_name << "' deleted Sprite compoment" << std::endl;
	}

	if (m_textComponent != nullptr)
	{
		delete m_textComponent;
		// std::cout << "\t The Object '" << m_name << "' deleted Text compoment" << std::endl;
	}
	
	// std::cout << "\t The Object '" << m_name << "' destroyed \n" << std::endl;
}


void Object::addRectComponent(int xPos, int yPos, int wSize, int hSize)
{
	if (m_rectComponent == nullptr)
	{
		m_rectComponent = new RectComponent(xPos, yPos, wSize, hSize);

		// std::cout << "\t The Object '" << m_name << "' added Rect compoment" << std::endl;
	}
}


void Object::addSpriteComponent(std::string path)
{
	if (m_spriteComponent == nullptr)
	{
		m_spriteComponent = new SpriteComponent(path);
		m_isGraphic = true;
		// std::cout << "\t The Object '" << m_name << "' added Sprite compoment" << std::endl;
	}
}


void Object::addTextComponent(const std::string& fontpath, int ptsize, const std::string& text)
{
	if (m_textComponent == nullptr)
	{
		m_textComponent = new TextComponent(fontpath, ptsize, text);
		m_isGraphic = true;
		// std::cout << "\t The Object '" << m_name << "' added Text compoment" << std::endl;
	}
}


void Object::addMusicComponent(std::string path, int volume)
{
	if (m_musicComponent == nullptr)
	{
		m_musicComponent = new MusicComponent(path, volume);

		// std::cout << "\t The Object '" << m_name << "' added Music compoment" << std::endl;
	}
}

void Object::addSoundComponent(std::string path)
{
	if (m_soundComponent == nullptr)
	{
		m_soundComponent = new SoundComponent(path);

		// std::cout << "\t The Object '" << m_name << "' added Sound compoment" << std::endl;
	}
}

void Object::setLayerPriority(LayerPriority priority)
{
	m_layerPriority = priority;
}


RectComponent* Object::getRectComponent()
{
	return m_rectComponent;
}


SpriteComponent* Object::getSpriteComponent()
{
	return m_spriteComponent;
}


TextComponent* Object::getTextComponent()
{
	return m_textComponent;
}


MusicComponent* Object::getMusicComponent()
{
	return m_musicComponent;
}

SoundComponent* Object::getSoundComponent()
{
	return m_soundComponent;
}


std::string Object::getName()  
{ 
	return m_name; 
}


bool Object::getGraphicState() 
{
	return m_isGraphic;
}


LayerPriority Object::getLayerPriority()
{
	return m_layerPriority;
}

