#include "Matrix3.h"

Matrix3::Matrix3()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
}

Matrix3::Matrix3(
	float m1, float m2, float m3,
	float m4, float m5, float m6,
	float m7, float m8, float m9
)
{
	m[0][0] = m1; m[0][1] = m4; m[0][2] = m7;
	m[1][0] = m2; m[1][1] = m5; m[1][2] = m8;
	m[2][0] = m3; m[2][1] = m6; m[2][2] = m9;
}

Vector3& Matrix3::operator[](int j)
{
	return (*reinterpret_cast<Vector3*>(m[j]));
}

const Vector3& Matrix3::operator[](int j) const
{
	return (*reinterpret_cast<const Vector3*>(m[j]));
}

float& Matrix3::operator()(int i, int j)
{
	return m[j][i];
}

const float& Matrix3::operator()(int i, int j) const
{
	return m[j][i];
}

Matrix3 operator*(const Matrix3& a, const Matrix3& b)
{
	return Matrix3(
		a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
		a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),

		a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
		a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
		a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),

		a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
		a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
		a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2)
	);
}

Vector3 operator*(const Matrix3& m, const Vector3& v)
{
	return Vector3(
		m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
		m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
		m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z
	);
}

float Determinant(const Matrix3& m)
{
	return
		m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
		m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
		m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
}

Matrix3 Inverse(const Matrix3& m)
{
	const Vector3& a = m[0];
	const Vector3& b = m[1];
	const Vector3& c = m[2];

	Vector3 r0 = Cross(b, c);
	Vector3 r1 = Cross(c, a);
	Vector3 r2 = Cross(a, b);

	float invDet = 1.0f / Dot(r2, c);
	return Matrix3(
		r0.x * invDet, r0.y * invDet, r0.z * invDet,
		r1.x * invDet, r1.y * invDet, r1.z * invDet,
		r2.x * invDet, r2.y * invDet, r2.z * invDet
	);
}

Matrix3 RotateX(const Matrix3& m, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);
	Matrix3 rot(
		1, 0, 0,
		0, c, -s,
		0, s, c
	);
	return m * rot;
}

Matrix3 RotateY(const Matrix3& m, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);
	Matrix3 rot(
		c, 0, s,
		0, 1, 0,
		-s, 0, c
	);
	return m * rot;
}

Matrix3 RotateZ(const Matrix3& m, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);
	Matrix3 rot(
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	);
	return m * rot;
}

Matrix3 Translate(const Matrix3& m, const Vector3& v)
{
	Matrix3 t(
		1, 0, v.x,
		0, 1, v.y,
		0, 0,  1
	);
	return m * t;
}

