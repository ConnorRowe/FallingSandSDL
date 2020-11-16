#include "Vector2.h"

Vector2::Vector2(int X, int Y)
{
	this->x = X;
	this->y = Y;
}

Vector2 Vector2::operator+(const Vector2& v)
{
	return Vector2(this->x + v.x, this->y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v)
{
	return Vector2(this->x - v.x, this->y - v.y);
}

Vector2 Vector2::operator*(const int& i)
{
	return Vector2(this->x * i, this->y * i);
}

bool Vector2::operator==(const Vector2& v)
{
	return this->x == v.x && this->y == v.y;
}

Vector2 Vector2::operator/(const int& i)
{
	return Vector2(this->x / i, this->y / i);
}

bool Vector2::operator!=(const Vector2& v)
{
	return this->x != v.x || this->y != v.y;
}
