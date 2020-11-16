#include "Vector2F.h"

Vector2F::Vector2F()
{
	this->x = 0;
	this->y = 0;
}

Vector2F::Vector2F(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

Vector2F Vector2F::operator+(const Vector2F& v)
{
	return Vector2F(this->x + v.x, this->y + v.y);
}

Vector2F Vector2F::operator-(const Vector2F& v)
{
	return Vector2F(this->x - v.x, this->y - v.y);
}

Vector2F Vector2F::operator*(const float& f)
{
	return Vector2F(this->x * f, this->y * f);
}
