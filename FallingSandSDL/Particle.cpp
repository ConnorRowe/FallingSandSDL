#include "Particle.h"

Particle::particle_t::particle_t()
{
	this->id = 0;
	this->lifetime = 0;
	this->velocity = Vector2F::ZERO();
	this->colour = SDL_Color{ 0,0,0,0 };
}

Particle::particle_t Particle::emptyParticle()
{
	return particle_t();
}

bool Particle::particle_t::isEmpty()
{
	return (this->id == 0);
}
