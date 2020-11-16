#pragma once
class Vector2F
{
public:
	float x;
	float y;

	Vector2F();
	Vector2F(float X, float Y);

	Vector2F operator+(const Vector2F& v);
	Vector2F operator-(const Vector2F& v);
	Vector2F operator*(const float& f);

	static Vector2F ZERO() {
		return Vector2F(0.0, 0.0);
	}
};

