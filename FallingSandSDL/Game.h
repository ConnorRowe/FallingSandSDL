#include "SDL.h"
#include "Vector2F.h"
#include <iostream>
#include <vector>
#include "Vector2.h"
#include "Particle.h"
#include "Grid.h"
#include "EFLAvE.h"

#pragma once
class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void eventHandler();
	void update(double deltaT);
	void render(double deltaT);
	void clean();

	bool running() { return isRunning; }

	void spawnParticle(Particle::particle_t particle, Vector2 pos);
	void spawnParticleLine(Particle::particle_t particle, Vector2 start, Vector2 end);

private:
	bool positiveFrame = false;
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

	bool applyGravity(Vector2 pos);
	bool applyTumble(Vector2 pos);
	bool applyFluidSpread(Vector2 pos, int spreadFactor);

	EFLAvE lineMaker;
	void makeLine(std::vector<Vector2>* positions, Vector2 start, Vector2 end);
};

