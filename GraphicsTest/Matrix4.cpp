#include "Matrix4.h"

Matrix4::Matrix4()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrix4::Matrix4(
	float m1,  float m2,  float m3,  float m4, 
	float m5,  float m6,  float m7,  float m8, 
	float m9,  float m10, float m11, float m12, 
	float m13, float m14, float m15, float m16
)
{
	m[0][0] = m1; m[0][1] = m5; m[0][2] = m9;  m[0][3] = m13;
	m[1][0] = m2; m[1][1] = m6; m[1][2] = m10; m[1][3] = m14;
	m[2][0] = m3; m[2][1] = m7; m[2][2] = m11; m[2][3] = m15;
	m[3][0] = m4; m[3][1] = m8; m[3][2] = m12; m[3][3] = m16;
}

Vector4& Matrix4::operator[](int j)
{
	return (*reinterpret_cast<Vector4*>(m[j]));
}

const Vector4& Matrix4::operator[](int j) const
{
	return (*reinterpret_cast<const Vector4*>(m[j]));
}

float& Matrix4::operator()(int i, int j)
{
	return m[j][i];
}

const float& Matrix4::operator()(int i, int j) const
{
	return m[j][i];
}

Matrix4 operator*(const Matrix4& a, float b)
{
	return Matrix4(
		a(0, 0) * b, a(0, 1) * b, a(0, 2) * b, a(0, 3) * b,
		a(1, 0) * b, a(1, 1) * b, a(1, 2) * b, a(1, 3) * b,
		a(2, 0) * b, a(2, 1) * b, a(2, 2) * b, a(2, 3) * b,
		a(3, 0) * b, a(3, 1) * b, a(3, 2) * b, a(3, 3) * b
	);
}

Matrix4 operator/(const Matrix4& a, float b)
{
	return a * (1 / b);
}

Matrix4 operator*(const Matrix4& a, const Matrix4& b)
{
	Matrix4 mat = Matrix4(
		a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1),
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) + a(0, 3) * b(3, 2),
		a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) * b(3, 3),

		a(1, 0)* b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) + a(1, 3) * b(3, 0),
		a(1, 0)* b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + a(1, 3) * b(3, 1),
		a(1, 0)* b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) + a(1, 3) * b(3, 2),
		a(1, 0)* b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) * b(3, 3),

		a(2, 0)* b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) + a(2, 3) * b(3, 0),
		a(2, 0)* b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) + a(2, 3) * b(3, 1),
		a(2, 0)* b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 2),
		a(2, 0)* b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3) * b(3, 3),

		a(3, 0)* b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + a(3, 3) * b(3, 0),
		a(3, 0)* b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + a(3, 3) * b(3, 1),
		a(3, 0)* b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + a(3, 3) * b(3, 2),
		a(3, 0)* b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) + a(3, 3) * b(3, 3)
	);

	return mat;
}

Vector4 operator*(const Matrix4& m, const Vector4& v)
{
	float a = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w;
	float b = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w;
	float c = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w;
	float d = m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z + m(3, 3) * v.w;
	Vector4 vec = Vector4(
		a, b, c, d
	);
	return vec;
}

float Determinant(const Matrix4& m)
{
	const Vector3& a = Vector3(m[0][0], m[0][1], m[0][2]);
	const Vector3& b = Vector3(m[1][0], m[1][1], m[1][2]);
	const Vector3& c = Vector3(m[2][0], m[2][1], m[2][2]);
	const Vector3& d = Vector3(m[3][0], m[3][1], m[3][2]);

	const float& x = m(3, 0);
	const float& y = m(3, 1);
	const float& z = m(3, 2);
	const float& w = m(3, 3);

	Vector3 s = Cross(a, b);
	Vector3 t = Cross(c, d);
	Vector3 u = a * y - b * x;
	Vector3 v = c * w - d * z;
	
	return Dot(s, v) + Dot(t, u);
}

Matrix4 Inverse(const Matrix4& m)
{
	const Vector3& a = m[0];
	const Vector3& b = m[1];
	const Vector3& c = m[2];
	const Vector3& d = m[3];

	const float& x = m(3.0f, 0);
	const float& y = m(3.0f, 1.0f);
	const float& z = m(3.0f, 2.0f);
	const float& w = m(3.0f, 3.0f);

	Vector3 s = Cross(a, b);
	Vector3 t = Cross(c, d);
	Vector3 u = a * y - b * x;
	Vector3 v = c * w - d * z;

	float invDet = 1.0f / (Dot(s, v) + Dot(t, u));

	s *= invDet;
	t *= invDet;
	u *= invDet;
	v *= invDet;

	Vector3 r0 = Cross(b, v) + t * y;
	Vector3 r1 = Cross(v, a) - t * x;
	Vector3 r2 = Cross(d, u) + s * w;
	Vector3 r3 = Cross(u, c) - s * z;

	return Matrix4(
		r0.x, r0.y, r0.z, -Dot(b, t),
		r1.x, r1.y, r1.z,  Dot(a, t),
		r2.x, r2.y, r2.z, -Dot(d, s),
		r3.x, r3.y, r3.z,  Dot(c, s)
	);
}

Matrix4 RotateX(const Matrix4& m, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);
	Matrix4 rot(
		1, 0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1
	);
	return m * rot;
}

Matrix4 RotateY(const Matrix4& m, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);
	Matrix4 rot(
		c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1
	);
	return m * rot;
}

Matrix4 RotateZ(const Matrix4& m, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);
	Matrix4 rot(
		c, -s, 0, 0, 
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	return m * rot;
}

Matrix4 Translate(const Matrix4& m, const Vector3& v)
{
	Matrix4 t(
		1, 0, 0, v.x,
		0, 1, 0, v.y,
		0, 0, 1, v.z,
		0, 0, 0, 1
	);
	return m * t;
}

Matrix4 Scale(const Matrix4 m, const Vector3 v)
{
	Matrix4 mScale(
		v.x, 0, 0, 0,
		0, v.y, 0, 0,
		0, 0, v.z, 0,
		0, 0, 0, 1
	);
	return m * mScale;
}
