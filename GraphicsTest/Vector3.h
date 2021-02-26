#pragma once
#include <math.h>
struct Vector4;

struct Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float a, float b, float c);
	Vector3(const Vector4& v);
	float& operator[](int i);
	const float& operator[](int i) const;
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
};

Vector3 operator+(const Vector3& a, const Vector3& b);
Vector3 operator-(const Vector3& a, const Vector3& b);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator*(const Vector3& v1, const Vector3& v2);
Vector3 operator/(const Vector3& v, float s);
Vector3 operator-(const Vector3& v);
float Magnitude(const Vector3& v);
Vector3 Normalize(const Vector3& v);
float Dot(const Vector3& a, const Vector3& b);
Vector3 Cross(const Vector3& a, const Vector3& b);
Vector3 Project(const Vector3& a, const Vector3& b);
Vector3 Reject(const Vector3& a, const Vector3& b);
Vector3 Reflect(const Vector3& a, const Vector3& b);