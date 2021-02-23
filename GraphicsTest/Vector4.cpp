#include "Vector4.h"
#include "Vector3.h"
Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}

Vector4::Vector4(const Vector3& v, float w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	this->w = w;
}

float& Vector4::operator[](int i)
{
	return (&x)[i];
}

const float& Vector4::operator[](int i) const
{
	return (&x)[i];
}

Vector4& Vector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Vector4& Vector4::operator/=(float s)
{
	s = 1 / s;
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4 operator+(const Vector4& a, const Vector4& b)
{
	return Vector4(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w
	);
}

Vector4 operator-(const Vector4& a, const Vector4& b)
{
	return Vector4(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w
	);
}

Vector4 operator*(const Vector4& v, float s)
{
	return Vector4(
		v.x * s,
		v.y * s,
		v.z * s,
		v.w * s
	);
}

Vector4 operator/(const Vector4& v, float s)
{
	s = 1 / s;
	return Vector4(
		v.x * s,
		v.y * s,
		v.z * s,
		v.w * s
	);
}

Vector4 operator-(const Vector4& v)
{
	return Vector4(
		-v.x,
		-v.y,
		-v.z,
		-v.w
	);
}

float Magnitude(const Vector4& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Vector4 Normalize(const Vector4& v)
{
	return v / Magnitude(v);
}

float Dot(const Vector4& a, const Vector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4 Cross(const Vector4& a, const Vector4& b)
{
	return Vector4(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		0
	);
}

Vector4 Project(const Vector4& a, const Vector4& b)
{
	return b * (Dot(a, b) / Dot(b, b));
}

Vector4 Reject(const Vector4& a, const Vector4& b)
{
	return a - b * (Dot(a, b) / Dot(b, b));
}
