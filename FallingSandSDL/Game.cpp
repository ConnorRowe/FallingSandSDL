#include "Game.h"

SDL_Event Game::event;

Game::Game()
{
	gridWidth = 192;
	gridHeight = 128;

	grid = Grid::Grid();
	grid.init(gridWidth, gridHeight);
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags == SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Initialised\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created successfully\n";
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 38, 38, 38, 255);

			std::cout << "Renderer created successfully\n";
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Game::eventHandler()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
	{
		switch (event.key.keysym.sym)
		{
		default:
			break;
		}
		break;
	}

	case SDL_KEYUP:
	{
		break;
	}

	case SDL_MOUSEBUTTONDOWN:
	{
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			leftMouseDown = true;
			break;

		case SDL_BUTTON_RIGHT:
			rightMouseDown = true;
			break;

		default:
			break;
		}
		break;
	}

	case SDL_MOUSEBUTTONUP:
	{
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			leftMouseDown = false;
			break;

		case SDL_BUTTON_RIGHT:
			rightMouseDown = false;
			break;

		default:
			break;
		}
		break;
	}

	case SDL_MOUSEMOTION:
	{
		mousePos.x = event.motion.x;
		mousePos.y = event.motion.y;
		break;
	}

	default:
		break;
	}
}

void Game::update(double deltaT)
{
	Particle::particle_t sand = Particle::emptyParticle();
	sand.id = 1;
	sand.colour = SDL_Colour{ 255,222,173,255 };

	Particle::particle_t water = Particle::emptyParticle();
	water.id = 2;
	water.colour = SDL_Colour{ 30,144,255,255 };

	if (leftMouseDown)
	{
		spawnParticle(sand, mousePos / 4);
	}
	else if (rightMouseDown)
	{
		spawnParticle(water, mousePos / 4);
	}


	// Update particles left to right from the bottom - up
	for (int x = 0; x < gridWidth; ++x)
		for (int y = gridHeight - 1; y >= 0; --y)
		{
			Particle::particle_t* p = grid.get(x, y);

			if (!p->isEmpty() && !p->hasBeenUpdated)
			{
				int speed = 10;
				p->hasBeenUpdated = true;
				Vector2 pos = Vector2(x, y);

				switch (p->id)
				{
				case 1:
				{
					// Sand

					if (!applyGravity(pos))
						applyTumble(pos);

					break;
				}
				case 2:
				{
					// Water

					if (!applyGravity(pos))
						if (!applyTumble(pos))
							applyFluidSpread(pos, 4);

					break;
				}
				default:
					break;
				}
			}
		}

	// Reset hasBeenUpdated
	grid.resetUpdate();

	positiveFrame = !positiveFrame;
}

void Game::render(double deltaT)
{
	SDL_RenderClear(renderer);
	// Render stuff here

	const int scale = 4;

	// Loop through grid
	for (int x = 0; x < gridWidth; ++x)
		for (int y = 0; y < gridHeight; ++y)
		{
			Particle::particle_t* p = grid.get(x, y);

			if (!p->isEmpty())
			{
				// Draw particle
				const SDL_Colour* col = &p->colour;

				SDL_SetRenderDrawColor(renderer, *(&col->r), *(&col->g), *(&col->b), *(&col->a));

				const SDL_Rect myRect{ x * scale,y * scale,scale,scale };
				SDL_RenderFillRect(renderer, &myRect);
			}
		}

	SDL_SetRenderDrawColor(renderer, 38, 38, 38, 255);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned\n";
}

void Game::spawnParticle(Particle::particle_t particle, Vector2 pos)
{
	if (grid.get(pos)->isEmpty())
	{
		grid.set(pos, particle);
	}
}

void Game::spawnParticleLine(Particle::particle_t particle, Vector2 start, Vector2 end)
{
	std::vector<Vector2> positions = std::vector<Vector2>();

	lineMaker.myLine(&positions, start.x, start.y, end.x, end.y);

	for (int i = 0; i < positions.size(); ++i)
	{
		spawnParticle(particle, positions.at(i));
	}
}

bool Game::applyGravity(Vector2 pos)
{
	// Gravity
	std::vector<Vector2> line = std::vector<Vector2>();
	makeLine(&line, pos, pos + Vector2(0, 10));

	for (int i = 1; i < line.size(); ++i)
	{
		Vector2* newPos = &line.at(i);
		if (grid.isPosWithinBounds(*newPos) && grid.isParticleEmpty(*newPos))
		{
			if (grid.isPosWithinBounds(*newPos) && grid.isParticleEmpty(*newPos))
			{
				// Move particle
				grid.set(*newPos, *grid.get(pos));

				// Clear old cell
				grid.set(pos, Particle::emptyParticle());

				return true;
			}
		}
	}

	return false;
}

bool Game::applyTumble(Vector2 pos)
{
	Vector2 translate = Vector2::ZERO();
	int x = pos.x;
	int y = pos.y;

	if (y + 1 < gridHeight && x - 1 >= 0 && grid.isParticleEmpty(x - 1, y + 1))
	{
		// Move down left
		translate.x = -1;
		translate.y = 1;
	}
	else if (y + 1 < gridHeight && x + 1 < gridWidth && grid.isParticleEmpty(x + 1, y + 1))
	{
		// Move down right
		translate.x = 1;
		translate.y = 1;
	}

	if (translate != Vector2::ZERO())
	{
		// Move particle
		grid.set(pos + translate, *grid.get(pos));

		// Clear old cell
		grid.set(pos, Particle::emptyParticle());

		return true;
	}

	return false;
}

bool Game::applyFluidSpread(Vector2 pos, int spreadFactor)
{
	int dir;
	if (positiveFrame)
		dir = -1;
	else
		dir = 1;

	// Fluid spread
	std::vector<Vector2> line = std::vector<Vector2>();
	makeLine(&line, pos, pos + Vector2(spreadFactor * dir, 0));

	// Can skip first one because it is == pos
	for (int i = 1; i < line.size(); ++i)
	{
		Vector2* newPos = &line.at(i);
		if (grid.isPosWithinBounds(*newPos) && grid.isParticleEmpty(*newPos))
		{
			// Move particle
			grid.set(*newPos, *grid.get(pos));

			// Clear old cell
			grid.set(pos, Particle::emptyParticle());

			return true;
		}
	}

	return false;
}

void Game::makeLine(std::vector<Vector2>* positions, Vector2 start, Vector2 end)
{
	lineMaker.myLine(positions, start.x, start.y, end.x, end.y);
}