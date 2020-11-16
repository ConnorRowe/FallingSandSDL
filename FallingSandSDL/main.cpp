#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	clock_t deltaTime = 0;
	unsigned int frames = 0;
	double  frameRate = 60;
	double  averageFrameTimeMilliseconds = 1000 / frameRate;

	game = new Game();

	game->init("Falling Sand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 512, false);

	while (game->running())
	{
		clock_t beginFrame = clock();

		game->eventHandler();
		game->update(averageFrameTimeMilliseconds);
		game->render(averageFrameTimeMilliseconds);

		clock_t endFrame = clock();

		deltaTime += endFrame - beginFrame;
		frames++;

		//if you really want FPS
		if (((deltaTime / (double)CLOCKS_PER_SEC) * 1000.0) > 1000.0) { //every second
			frameRate = (double)frames * 0.5 + frameRate * 0.5; //more stable
			frames = 0;
			deltaTime -= CLOCKS_PER_SEC;
			averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

			if (true)
				std::cout << "FrameTime was:" << averageFrameTimeMilliseconds << std::endl;
			else
				std::cout << "CPU time was:" << averageFrameTimeMilliseconds << std::endl;
		}
	}

	game->clean();

	return 0;
}

double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}