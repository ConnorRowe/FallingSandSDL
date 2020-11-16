#include "Grid.h"

void Grid::init(size_t width, size_t height)
{
	this->length = width * height;
	this->width = width;
	this->height = height;

	// Create array
	ary = new Particle::particle_t[length];

	// Fill array
	for (size_t i = 0; i < length; ++i)
	{
		ary[i] = Particle::emptyParticle();
	}

	std::cout << "Using: Extremely Fast Line Algorithm Var E (Addition Fixed Point PreCalc)\nCopyright 2001-2, By Po-Han Lin\nhttp://www.edepot.com/algorithm.html\n";
}

Particle::particle_t* Grid::get(int x, int y)
{
	if (x < 0 || x >= width)
	{
		std::cout << "x (" << x << ") out of bounds during Grid::get\n";

		return nullptr;
	}
	else if (y < 0 || y >= height)
	{
		std::cout << "y (" << y << ") out of bounds during Grid::get\n";
		return nullptr;
	}

	return &ary[index(x, y)];
}

void Grid::resetUpdate()
{
	for (int i = 0; i < length; ++i)
	{
		ary[i].hasBeenUpdated = false;
	}
}

bool Grid::isParticleEmpty(int x, int y)
{
	return get(x, y)->isEmpty();
}
