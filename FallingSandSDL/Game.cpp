#include "Game.h"

SDL_Event Game::event;

Game::Game()
{
	gridWidth = 192;
	gridHeight = 128;

	// Allocate grid array
	grid = new particle_t * [gridWidth];
	for (int i = 0; i < gridWidth; ++i)
		grid[i] = new particle_t[gridHeight];

	// Fill
	for (int i = 0; i < gridWidth; ++i)
		for (int j = 0; j < gridHeight; ++j)
			grid[i][j] = emptyParticle();


	// Set top line
	//particle_t sand = emptyParticle();
	//sand.id = 1;
	//for (int i = 0; i < gridWidth; ++i)
	//{
	//	grid[i][0] = sand;
	//}
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

void Game::update()
{
	particle_t sand = emptyParticle();
	sand.id = 1;
	sand.colour = SDL_Colour{ 255,222,173,255 };

	particle_t water = emptyParticle();
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


	// Update particles
	for (int x = 0; x < gridWidth; ++x)
		for (int y = 0; y < gridHeight; ++y)
		{
			Vector2 translate = Vector2::ZERO();

			if (!grid[x][y].isEmpty() && !grid[x][y].hasBeenUpdated)
			{
				grid[x][y].hasBeenUpdated = true;

				switch (grid[x][y].id)
				{
				case 1:
					updateSand(Vector2(x, y));
					break;
				case 2:
					updateWater(Vector2(x, y));
					break;
				default:
					break;
				}
			}
		}

	// Reset hasBeenUpdated
	for (int i = 0; i < gridWidth; ++i)
		for (int j = 0; j < gridHeight; ++j)
		{
			if (!grid[i][j].isEmpty() && grid[i][j].hasBeenUpdated)
			{
				grid[i][j].hasBeenUpdated = false;
			}
		}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// Render stuff here

	const int scale = 4;

	// Loop through grid
	for (int x = 0; x < gridWidth; ++x)
		for (int y = 0; y < gridHeight; ++y)
		{
			if (!grid[x][y].isEmpty())
			{
				// Draw particle
				const SDL_Colour* col = &grid[x][y].colour;

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

	// Free grid array
	for (int i = 0; i < gridWidth; ++i)
		delete[] grid[i];
	delete[] grid;

	std::cout << "Game cleaned\n";
}

Game::particle_t::particle_t()
{
	this->id = 0;
	this->lifetime = 0;
	this->velocity = Vector2F::ZERO();
	this->colour = SDL_Color{ 0,0,0,0 };
}

bool Game::particle_t::isEmpty()
{
	return (this->id == 0);
}

void Game::spawnParticle(particle_t particle, Vector2 pos)
{
	if (grid[pos.x][pos.y].isEmpty())
	{
		grid[pos.x][pos.y] = particle;
	}
}

Game::particle_t Game::emptyParticle()
{
	return particle_t();
}

bool Game::updateSand(Vector2 pos)
{
	int x = pos.x;
	int y = pos.y;

	Vector2 translate = Vector2::ZERO();

	// Check cell below
	if (y + 1 <= gridHeight && grid[x][y + 1].isEmpty())
	{
		// Move down
		translate.y = 1;
	}
	else if (y + 1 <= gridHeight && x - 1 >= 0 && grid[x - 1][y + 1].isEmpty())
	{
		// Move down left
		translate.x = -1;
		translate.y = 1;
	}
	else if (y + 1 <= gridHeight && x + 1 < gridWidth && grid[x + 1][y + 1].isEmpty())
	{
		// Move down right
		translate.x = 1;
		translate.y = 1;
	}

	if (translate != Vector2::ZERO())
	{
		// Move particle
		grid[x + translate.x][y + translate.y] = grid[x][y];

		// Clear old cell
		grid[x][y] = emptyParticle();

		return true;
	}

	return false;
}

bool Game::updateWater(Vector2 pos)
{
	if (updateSand(pos))
		return true;
	else
	{
		int x = pos.x;
		int y = pos.y;

		Vector2 translate = Vector2::ZERO();

		if (x - 1 >= 0 && grid[x - 1][y].isEmpty())
		{
			translate.x = -1;
		}
		else if (x + 1 < gridWidth && grid[x + 1][y].isEmpty())
		{
			translate.x = 1;
		}

		if (translate != Vector2::ZERO())
		{
			// Move particle
			grid[x + translate.x][y + translate.y] = grid[x][y];

			// Clear old cell
			grid[x][y] = emptyParticle();

			return true;
		}
	}

	return false;
}
