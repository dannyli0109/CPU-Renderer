#pragma once
#include "Vector3.h"

struct Matrix3
{
public:
	Matrix3();
	Matrix3(
		float m1, float m2, float m3,
		float m4, float m5, float m6,
		float m7, float m8, float m9
	);

	Vector3& operator[](int j);
	const Vector3& operator[](int j) const;
	float& operator()(int i, int j);
	const float& operator()(int i, int j) const;

private:
	float m[3][3];
};

Matrix3 operator*(const Matrix3& a, const Matrix3& b);
Vector3 operator*(const Matrix3& m, const Vector3& v);
Matrix3 operator*(const Matrix3& m, float s);
Matrix3 operator+(const Matrix3& m1, const Matrix3& m2);
float Determinant(const Matrix3& m);
Matrix3 Inverse(const Matrix3& m);
Matrix3 RotateX(const Matrix3& m, float radian);
Matrix3 RotateY(const Matrix3& m, float radian);
Matrix3 RotateZ(const Matrix3& m, float radian);
//Matrix3 Translate(const Matrix3& m, const Vector2& v); 