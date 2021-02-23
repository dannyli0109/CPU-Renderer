#include "Vector3.h"
#include "Vector4.h"
Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vector3::Vector3(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

float& Vector3::operator[](int i)
{
	return ((&x)[i]);
}

const float& Vector3::operator[](int i) const
{
	return ((&x)[i]);
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	s = 1.0f / s;
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 operator*(const Vector3& v, float s)
{
	return Vector3(v.x * s, v.y * s, v.z * s);
}

Vector3 operator/(const Vector3& v, float s)
{
	s = 1.0f / s;
	return Vector3(v.x * s, v.y * s, v.z * s);
}

Vector3 operator-(const Vector3& v)
{
	return Vector3(-v.x, -v.y, -v.z);
}

float Magnitude(const Vector3& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v)
{
	float mag = Magnitude(v);
	if (mag == 0) return Vector3();
	return v / Magnitude(v);
}

float Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

Vector3 Project(const Vector3& a, const Vector3& b)
{
	return b * (Dot(a, b) / Dot(b, b));
}

Vector3 Reject(const Vector3& a, const Vector3& b)
{
	return a - b * (Dot(a, b) / Dot(b, b));
}
