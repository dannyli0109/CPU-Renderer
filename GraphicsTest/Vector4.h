#pragma once
#include <math.h>
struct Vector3;
struct Vector4
{
public:
	float x, y, z, w;
	Vector4();
	Vector4(float a, float b, float c, float d);
	Vector4(const Vector3& v, float w);
	float& operator[](int i);
	const float& operator[](int i) const;
	Vector4& operator*=(float s);
	Vector4& operator/=(float s);
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
};

Vector4 operator+(const Vector4& a, const Vector4& b);
Vector4 operator-(const Vector4& a, const Vector4& b);
Vector4 operator*(const Vector4& v, float s);
Vector4 operator*(const Vector4& v1, const Vector4& v2);

Vector4 operator/(const Vector4& v, float s);
Vector4 operator-(const Vector4& v);
float Magnitude(const Vector4& v);
Vector4 Normalize(const Vector4& v);
float Dot(const Vector4& a, const Vector4& b);
Vector4 Cross(const Vector4& a, const Vector4& b);
Vector4 Project(const Vector4& a, const Vector4& b);
Vector4 Reject(const Vector4& a, const Vector4& b);

