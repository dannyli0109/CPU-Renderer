#pragma once
#include <math.h>
struct Vector2
{
	float x, y;
	Vector2();
	Vector2(float a, float b);
	float& operator[](int i);
	const float& operator[](int i) const;
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
};

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& v, float s);
Vector2 operator/(const Vector2& v, float s);
Vector2 operator-(const Vector2& v);
float Magnitude(const Vector2& v);
Vector2 Normalize(const Vector2& v);
float Dot(const Vector2& a, const Vector2& b);

