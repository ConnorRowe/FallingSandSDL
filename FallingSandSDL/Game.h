#include "SDL.h"
#include "Vector2F.h"
#include <iostream>
#include "Vector2.h"
#include "Particle.h"
#include "Grid.h"

#pragma once
class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void eventHandler();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	void spawnParticle(Particle::particle_t particle, Vector2 pos);

private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Vector2 mousePos = Vector2::ZERO();
	bool leftMouseDown = false;
	bool rightMouseDown = false;

	int gridWidth;
	int gridHeight;

	Grid grid;

	static SDL_Event event;

	bool updateSand(Vector2 pos);
	bool updateWater(Vector2 pos);
};

