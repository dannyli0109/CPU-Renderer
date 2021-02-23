#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float a, float b)
{
	x = a;
	y = b;
}

float& Vector2::operator[](int i)
{
	return (&x)[i];
}

const float& Vector2::operator[](int i) const
{
	return (&x)[i];
}

Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s)
{
	s = 1 / s;
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 operator+(const Vector2& a, const Vector2& b)
{
	return Vector2(
		a.x + b.x, a.y + b.y
	);
}

Vector2 operator-(const Vector2& a, const Vector2& b)
{
	return Vector2(
		a.x - b.x, a.y - b.y
	);
}

Vector2 operator*(const Vector2& v, float s)
{
	return Vector2(
		v.x * s, v.y * s
	);
}

Vector2 operator/(const Vector2& v, float s)
{
	s = 1 / s;
	return Vector2(
		v.x * s, v.y * s
	);
}

Vector2 operator-(const Vector2& v)
{
	return Vector2(
		-v.x, -v.y
	);
}

float Magnitude(const Vector2& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2 Normalize(const Vector2& v)
{
	float mag = Magnitude(v);
	return v / mag;
}

float Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}
