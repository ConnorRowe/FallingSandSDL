#include "SDL.h"
#include "Vector2F.h"
#include <iostream>
#include "Vector2.h"

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

	typedef struct particle_t
	{
		int id;
		float lifetime;
		Vector2F velocity;
		SDL_Colour colour;
		bool hasBeenUpdated = false;

		particle_t();

		bool isEmpty();
	};

	void spawnParticle(particle_t particle, Vector2 pos);

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
	particle_t** grid;

	particle_t emptyParticle();

	static SDL_Event event;

	bool updateSand(Vector2 pos);
	bool updateWater(Vector2 pos);
};

