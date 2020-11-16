#pragma once
class Vector2
{
public:
	int x;
	int y;

	Vector2(int X, int Y);

	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator*(const int& i);
	Vector2 operator/(const int& i);
	bool operator==(const Vector2& v);
	bool operator!=(const Vector2& v);

	static Vector2 ZERO() {
		return Vector2(0, 0);
	}
};

