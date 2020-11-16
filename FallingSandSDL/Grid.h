#include "Vector2.h"
#include "Particle.h"
#include <iostream>

#pragma once
class Grid
{
public:
	void init(size_t width, size_t height);
	// Convert x, y coords into an array index
	size_t index(int x, int y) const { return x + width * y; }
	Particle::particle_t* get(int x, int y);
	Particle::particle_t* get(Vector2 pos) { return get(pos.x, pos.y); }
	void set(int x, int y, Particle::particle_t p) { ary[index(x, y)] = p; }
	void set(Vector2 pos, Particle::particle_t p) { set(pos.x, pos.y, p); }
	size_t getLength() { return length; }
	void resetUpdate();
	bool isParticleEmpty(int x, int y);

private:
	size_t width;
	size_t height;
	size_t length;

	Particle::particle_t* ary;
};

