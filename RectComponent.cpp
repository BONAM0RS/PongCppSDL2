
// C++ Standard Libraries
#include <iostream>

// This Class header
#include "RectComponent.h"


RectComponent::RectComponent(int xPos, int yPos, int wSize, int hSize)
	: m_trackingParams { 0, 0, 0 }
{
	setRect(xPos, yPos, wSize, hSize);
	saveInitState();

	// std::cout << "\t Rectangle component created" << std::endl;
}


RectComponent::~RectComponent()
{
	// std::cout << "\t Rectangle component destroyed" << std::endl;
}


void RectComponent::setRect(int xPos, int yPos, int wSize, int hSize)
{
	m_trackingRect.x = xPos;
	m_trackingRect.y = yPos;
	m_trackingRect.w = wSize;
	m_trackingRect.h = hSize;
}


void RectComponent::setPosition(int xPos, int yPos)
{
	m_trackingRect.x = xPos;
	m_trackingRect.y = yPos;
}


void RectComponent::setSize(int wSize, int hSize)
{
	m_trackingRect.w = wSize;
	m_trackingRect.h = hSize;
}


void RectComponent::setPosX(int xPos)    { m_trackingRect.x = xPos;  }
void RectComponent::setPosY(int yPos)    { m_trackingRect.y = yPos;  }
void RectComponent::setWidth(int wSize)  { m_trackingRect.w = wSize; }
void RectComponent::setHeight(int hSize) { m_trackingRect.h = hSize; }


void RectComponent::setMovement(int xDir, int yDir, int speed)
{
	m_trackingParams.dirX = xDir;
	m_trackingParams.dirY = yDir;
	m_trackingParams.spd = speed;
}


void RectComponent::setDirection(int xDir, int yDir)
{
	m_trackingParams.dirX = xDir;
	m_trackingParams.dirY = yDir;
}


void RectComponent::setDirX(int xDir)   { m_trackingParams.dirX = xDir;  }
void RectComponent::setDirY(int yDir)   { m_trackingParams.dirY = yDir;  }
void RectComponent::setSpeed(int speed) { m_trackingParams.spd = speed; }


void RectComponent::move()
{
	if (m_trackingParams.spd != 0)
	{
		if (m_trackingParams.dirX != 0) { m_trackingRect.x += m_trackingParams.dirX * m_trackingParams.spd; }
		if (m_trackingParams.dirY != 0) { m_trackingRect.y += m_trackingParams.dirY * m_trackingParams.spd; }
	}
}


void RectComponent::saveInitState()
{
	m_initialRect = m_trackingRect;
	m_initialParams = m_trackingParams;
}


void RectComponent::loadInitState()
{
	m_trackingRect = m_initialRect;
	m_trackingParams = m_initialParams;
}


int RectComponent::checkWindowCollision(int wScreen, int hScreen)
{
	if (m_trackingRect.x <= m_trackingParams.spd)                               { return 1; } // left border
	if (m_trackingRect.x + m_trackingRect.w >= wScreen - m_trackingParams.spd)  { return 2; } // right border    
	if (m_trackingRect.y <= m_trackingParams.spd)                               { return 3; } // top border     
	if (m_trackingRect.y + m_trackingRect.h >= hScreen - m_trackingParams.spd)  { return 4; } // bottom border

	return 0; // no collision
}


SDL_bool RectComponent::isColliding(RectComponent& rectObject)
{
	const SDL_Rect* object1 = &m_trackingRect;
	const SDL_Rect* object2 = &rectObject.m_trackingRect;
	return SDL_HasIntersection(object1, object2);
}


SDL_Rect RectComponent::getRect()
{ 
	return m_trackingRect; 
}


int RectComponent::getPosX()   { return m_trackingRect.x; }
int RectComponent::getPosY()   { return m_trackingRect.y; }
int RectComponent::getWidth()  { return m_trackingRect.w; }
int RectComponent::getHeight() { return m_trackingRect.h; }


int RectComponent::getDirX()  { return m_trackingParams.dirX; }
int RectComponent::getDirY()  { return m_trackingParams.dirY; }
int RectComponent::getSpeed() { return m_trackingParams.spd; }

