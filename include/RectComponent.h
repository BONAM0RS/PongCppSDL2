
#pragma once

// C++ Standard Libraries
//

// SDL Libraries
#include <SDL.h>

// Class Headers
//


class RectComponent {

public:
	RectComponent(int xPos = 0, int yPos = 0, int wSize = 0, int hSize = 0);
	~RectComponent();

	void setRect(int xPos, int yPos, int wSize, int hSize);
	void setPosition(int xPos, int yPos);
	void setSize(int wSize, int hSize);
	
	void setPosX(int xPos);
	void setPosY(int yPos);
	void setWidth(int wSize);
	void setHeight(int hSize);

	void setMovement(int xDir, int yDir, int speed);
	void setDirection(int xDir, int yDir);
	void setDirX(int xDir);
	void setDirY(int yDir);
	void setSpeed(int speed);

	void move();

	void saveInitState();
	void loadInitState();

	SDL_Rect getRect() const;
	int getPosX() const;
	int getPosY() const;
	int getWidth() const;
	int getHeight() const;
	int getDirX() const;
	int getDirY() const;
	int getSpeed() const;

	int checkWindowCollision(int wScreen, int hScreen);

	SDL_bool isColliding(RectComponent& rectObject);

protected:
	SDL_Rect m_initialRect;
	SDL_Rect m_trackingRect;

	struct Params { int dirX; int dirY; int spd; };
	Params m_initialParams;
	Params m_trackingParams;
};