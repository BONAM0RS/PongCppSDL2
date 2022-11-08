
#pragma once

#include <string>

// Class Headers
#include "Framework.h"


class Pong : public Framework {

public:
	Pong(Uint32 subsystemFlags, const char* title, int xPos, int yPos, int wSize, int hSize);
	virtual ~Pong();

	virtual bool Init();

	virtual void Close();

	virtual void Tick();

	virtual void KeyPressedEvent(FRKey k);

	virtual void KeyReleasedEvent(FRKey k);

	void moveObjects();
	void checkObjectsCollision();
	void checkScreenCollision();
	void calculateEnemyAI();
	void updateScore();
	void resetObjects();

	void playGame();
	void pauseGame();
	void restartGame();

	int getRandomDir();

private:
	static const int DEFAULT_WINDOW_WIDTH = 800;
	static const int DEFAULT_WINDOW_HEIGHT = 600;

	static const int PADDLE_WIDTH = 25;
	static const int PADDLE_HEIGHT = 150;
	static const int PADDLE_WIDTH_HALF = PADDLE_WIDTH / 2;
	static const int PADDLE_HEIGHT_HALF = PADDLE_HEIGHT / 2;
	static const int PADDLE_SPEED = 7;

	static const int BALL_SIZE = 20;
	static const int BALL_SIZE_HALF = BALL_SIZE / 2;
	static const int BALL_SPEED = 9;

	static const int SCORE_WIDTH = 100;
	static const int SCORE_HEIGHT = 50;
	static const int SCORE_WIDTH_HALF = SCORE_WIDTH / 2;
	static const int SCORE_HEIGHT_HALF = SCORE_HEIGHT / 2;

	std::shared_ptr<Object> background_1;
	std::shared_ptr<Object> background_2;
	std::shared_ptr<Object> paddleLeft;
	std::shared_ptr<Object> paddleRight;
	std::shared_ptr<Object> ball;
	std::shared_ptr<Object> score;
	std::shared_ptr<Object> backgroundMusic;
	std::shared_ptr<Object> collideSound;
	std::shared_ptr<Object> scoreSound;
	
	const char* backgroundImagePath = "./images/background.png";

	const char* paddleImagePath = "./images/paddle.png";
	const char* ballImagePath = "./images/ball.png";

	const char* peepoFontPath = "./fonts/Peepo.ttf";

	const char* backgroundMusicPath = "./music/background.mp3";

	const char* collideSoundPath = "./sounds/collide.wav";
	const char* scoreSoundPath = "./sounds/score.wav";

	int scoreLeft;
	int scoreRight;

	std::string scoreText;

	bool isPause;

	bool isMoveUp;
	bool isMoveDown;

	bool isMovePaddle;
};

