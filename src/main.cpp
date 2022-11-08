
// Game Class Header
#include "Pong.h"


int main(int argc, char* argv[])
{
	const Uint32 subsystemFlags = SDL_INIT_VIDEO;

	const char* TITLE = "Pong";

	const int WINDOW_POS_X = 560;
	const int WINDOW_POS_Y = 240;

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	return run(new Pong(subsystemFlags, TITLE, WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT));
}

