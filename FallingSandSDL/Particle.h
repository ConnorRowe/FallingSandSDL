#include "Vector2F.h"
#include <SDL_pixels.h>

#pragma once
class Particle
{
public:
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

	static particle_t emptyParticle();
};

