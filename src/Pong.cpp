
// C++ Standard Libraries
#include <iostream>
#include <string> //

// Class Headers
#include "ObjectManager.h"

// This Class header
#include "Pong.h"


Pong::Pong(Uint32 subsystemFlags, const char* title, int xPos, int yPos, int wSize, int hSize)
	: Framework    { subsystemFlags, title, xPos, yPos, wSize, hSize },
	  scoreLeft    { 0 },
	  scoreRight   { 0 },
	  isPause      { false },
	  isMoveUp     { false },
	  isMoveDown   { false },
	  isMovePaddle { true  }
{
	// std::cout << " GAME CREATED \n" << std::endl;
}


Pong::~Pong()
{
	// std::cout << " GAME DESTROYED \n" << std::endl;
}


bool Pong::Init()
{
	std::cout << " GAME INIT STARTED \n" << std::endl;

	srand((unsigned int)time(0));
	
	// Create objects
	createObject("background_1", LayerPriority::BACKGROUND);
	createObject("background_2", LayerPriority::BACKGROUND);
	createObject("paddleLeft", LayerPriority::MIDDLEGROUND);
	createObject("paddleRight", LayerPriority::MIDDLEGROUND);
	createObject("ball", LayerPriority::MIDDLEGROUND);
	createObject("score", LayerPriority::FOREGROUND);
	createObject("backgroundMusic");
	createObject("collideSound");
	createObject("scoreSound");
	
	// Init objects
	background_1 = getObjectByName("background_1");
	background_2 = getObjectByName("background_2");
	paddleLeft = getObjectByName("paddleLeft");
	paddleRight = getObjectByName("paddleRight");
	ball = getObjectByName("ball");
	score = getObjectByName("score");
	backgroundMusic = getObjectByName("backgroundMusic");
	collideSound = getObjectByName("collideSound");
	scoreSound = getObjectByName("scoreSound");

	// Setup Background
	background_1->addRectComponent(0, 0, getScreenWidth(), getScreenHeight());
	background_2->addRectComponent(0, -getScreenHeight(), getScreenWidth(), getScreenHeight());

	background_1->addSpriteComponent(backgroundImagePath);
	background_2->addSpriteComponent(backgroundImagePath);

	background_1->getRectComponent()->setMovement(0, 1, 1);
	background_2->getRectComponent()->setMovement(0, 1, 1);

	// Setup left Paddle
	int posX = PADDLE_HEIGHT_HALF;
	int posY = getScreenHeightHalf() - PADDLE_HEIGHT_HALF;
	paddleLeft->addRectComponent(posX, posY, PADDLE_WIDTH, PADDLE_HEIGHT);
	paddleLeft->addSpriteComponent(paddleImagePath);

	paddleLeft->getRectComponent()->setSpeed(PADDLE_SPEED);
	paddleLeft->getRectComponent()->saveInitState();
	
	// Setup right Paddle
	posX = getScreenWidth() - PADDLE_WIDTH - PADDLE_HEIGHT_HALF;
	paddleRight->addRectComponent(posX, posY, PADDLE_WIDTH, PADDLE_HEIGHT);
	paddleRight->addSpriteComponent(paddleImagePath);

	paddleRight->getRectComponent()->setSpeed(PADDLE_SPEED);
	paddleRight->getRectComponent()->saveInitState();
	
	// Setup ball
	posX = getScreenWidthHalf() - BALL_SIZE_HALF;
	posY = getScreenHeightHalf() - BALL_SIZE_HALF;
	ball->addRectComponent(posX, posY, BALL_SIZE, BALL_SIZE);
	ball->addSpriteComponent(ballImagePath);

	ball->getRectComponent()->setMovement(getRandomDir(), 0, BALL_SPEED);
	ball->getRectComponent()->saveInitState();

	// Setup score
	posX = getScreenWidthHalf() - SCORE_WIDTH_HALF;
	posY = SCORE_HEIGHT_HALF;
	scoreText = std::to_string(scoreLeft) + " | " + std::to_string(scoreRight);
	score->addRectComponent(posX, posY, SCORE_WIDTH, SCORE_HEIGHT);
	score->addTextComponent(peepoFontPath, 20, scoreText);
	
	// Setup background music
	backgroundMusic->addMusicComponent(backgroundMusicPath, 30);
	backgroundMusic->getMusicComponent()->playMusic(-1);

	// Setup collide sound
	collideSound->addSoundComponent(collideSoundPath);

	// Setup score sound
	scoreSound->addSoundComponent(scoreSoundPath);

	std::cout << "\n GAME INIT FINISHED \n" << std::endl;

	return true;
}


void Pong::Close()
{
	ObjectManager::getInstance().deleteAllObjects();

	std::cout << "\n GAME CLOSED \n" << std::endl;
}


void Pong::Tick()
{
	if (isPause == false)
	{
		moveObjects();
		calculateEnemyAI();
		checkObjectsCollision();
		checkScreenCollision();
	}
}


void Pong::moveObjects()
{
	background_1->getRectComponent()->move();
	background_2->getRectComponent()->move();

	
	if (background_1->getRectComponent()->getPosY() == getScreenHeight())
	{
		background_1->getRectComponent()->setPosY(-getScreenHeight());
	}

	else if (background_2->getRectComponent()->getPosY() == getScreenHeight())
	{
		background_2->getRectComponent()->setPosY(-getScreenHeight());
	}
	

	ball->getRectComponent()->move();

	if (isMovePaddle == true)
	{
		if (isMoveUp == true || isMoveDown == true)
		{
			paddleLeft->getRectComponent()->move();
			
		}
	}

	paddleRight->getRectComponent()->move();
}


void Pong::calculateEnemyAI()
{
	int enemyCenterPoint = paddleRight->getRectComponent()->getPosY() + PADDLE_HEIGHT_HALF;

	if ((ball->getRectComponent()->getPosY()) <= enemyCenterPoint)
	{
		paddleRight->getRectComponent()->setDirY(-1);
	}
	else
	{
		paddleRight->getRectComponent()->setDirY(1);
	}

	if (ball->getRectComponent()->getDirY() == 0)
	{
		paddleRight->getRectComponent()->setDirY(0);
	}
}


void Pong::checkObjectsCollision()
{
	// Ball with left Paddle
	if (ball->getRectComponent()->isColliding(*paddleLeft->getRectComponent()))
	{
		collideSound->getSoundComponent()->playSound();

		ball->getRectComponent()->setDirX(1);

		if (paddleLeft->getRectComponent()->getDirY() == 0)

		{
			if (ball->getRectComponent()->getDirY() != 0)
			{
				ball->getRectComponent()->setDirY(0);
			}
			else
			{
				ball->getRectComponent()->setDirY(getRandomDir());
			}
		}

		else if (paddleLeft->getRectComponent()->getDirY() == 1)
		{
			ball->getRectComponent()->setDirY(1);
		}

		else if (paddleLeft->getRectComponent()->getDirY() == -1)
		{
			ball->getRectComponent()->setDirY(-1);
		}
	}

	// Ball with right Paddle
	if (ball->getRectComponent()->isColliding(*paddleRight->getRectComponent()))
	{
		collideSound->getSoundComponent()->playSound();

		ball->getRectComponent()->setDirX(-1);

		if (paddleRight->getRectComponent()->getDirY() == 0)

		{
			if (ball->getRectComponent()->getDirY() != 0)
			{
				ball->getRectComponent()->setDirY(0);
			}
			else
			{
				ball->getRectComponent()->setDirY(getRandomDir());
			}
		}

		else if (paddleRight->getRectComponent()->getDirY() == 1)
		{
			ball->getRectComponent()->setDirY(1);
		}

		else if (paddleRight->getRectComponent()->getDirY() == -1)
		{
			ball->getRectComponent()->setDirY(-1);
		}
	}
}


int Pong::getRandomDir()
{
	int randomDir = rand() % 2;

	switch (randomDir)
	{
	case 0: { randomDir = -1; break; }
	case 1: { randomDir = 1; break; }
	}

	return randomDir;
}


void Pong::checkScreenCollision()
{
	// Ball
	switch (ball->getRectComponent()->checkWindowCollision(getScreenWidth(), getScreenHeight()))
	{
		case 1: { resetObjects(); scoreLeft++;  updateScore(); ball->getRectComponent()->setDirX(-1); break; } // left border
		case 2: { resetObjects(); scoreRight++; updateScore(); ball->getRectComponent()->setDirX( 1); break; } // right border 

		case 3: { ball->getRectComponent()->setDirY( 1); break; } // top border
		case 4: { ball->getRectComponent()->setDirY(-1); break; } // bottom border
	}

	// Paddle
	switch (paddleLeft->getRectComponent()->checkWindowCollision(getScreenWidth(), getScreenHeight()))
	{
		case 3: // top border
		{
			if (isMoveUp == true) 
			{ 
				isMovePaddle = false; 
			}
			else 
			{ 
				isMovePaddle = true; 
			}

			break;
		}

		case 4: // bottom border
		{
			if (isMoveDown == true) 
			{ 
				isMovePaddle = false; 
			}
			else 
			{ 
				isMovePaddle = true; 
			}

			break;
		}
	}


	switch (paddleRight->getRectComponent()->checkWindowCollision(getScreenWidth(), getScreenHeight()))
	{
		case 3: // top border
		{
			if (paddleRight->getRectComponent()->getDirY() != 1)
			{
				paddleRight->getRectComponent()->setDirY(0);
			}
		
			break;
		}

		case 4: // bottom border
		{
			if (paddleRight->getRectComponent()->getDirY() != -1)
			{
				paddleRight->getRectComponent()->setDirY(0);
			}
		
			break;
		}
	}
}


void Pong::updateScore()
{
	scoreText = std::to_string(scoreLeft) + " | " + std::to_string(scoreRight);
	score->getTextComponent()->setText(scoreText);

	scoreSound->getSoundComponent()->playSound();

	if (scoreLeft == 11 || scoreRight == 11)
	{
		restartGame();
	}
}


void Pong::resetObjects()
{
	paddleLeft->getRectComponent()->loadInitState();
	paddleRight->getRectComponent()->loadInitState();
	ball->getRectComponent()->loadInitState();

	isMovePaddle = true;
}



void Pong::KeyPressedEvent(FRKey k)
{
	switch (k)
	{
		case FRKey::UP:   { isMoveUp = true;  isMoveDown = false; paddleLeft->getRectComponent()->setDirY(-1); break; }
		case FRKey::DOWN: {	isMoveUp = false; isMoveDown = true;  paddleLeft->getRectComponent()->setDirY( 1); break; }
	}
}


void Pong::KeyReleasedEvent(FRKey k)
{
	switch (k)
	{
		case FRKey::UP:   { isMoveUp   = false; paddleLeft->getRectComponent()->setDirY(0); break; }
		case FRKey::DOWN: { isMoveDown = false; paddleLeft->getRectComponent()->setDirY(0); break; }

		case FRKey::P:	  { pauseGame(); break; }
		case FRKey::R:    { restartGame(); break; }
	}
}


void Pong::pauseGame()
{
	if (isPause == false)
	{
		isPause = true;
	}
	else
	{
		playGame();
	}
	
}


void Pong::playGame()
{
	isPause = false;
}


void Pong::restartGame()
{
	scoreLeft = 0;
	scoreRight = 0;

	updateScore();
	resetObjects();

	ball->getRectComponent()->setDirX(getRandomDir());
}


