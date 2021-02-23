#pragma once
#include "Vector4.h"
#include "Vector3.h"
struct Matrix4
{
public:
	Matrix4();
	Matrix4(
		float m1,  float m2,  float m3,  float m4, 
		float m5,  float m6,  float m7,  float m8, 
		float m9,  float m10, float m11, float m12, 
		float m13, float m14, float m15, float m16
	);
	Vector4& operator[](int j);
	const Vector4& operator[](int j) const;
	float& operator()(int i, int j);
	const float& operator()(int i, int j) const;

private:
	float m[4][4];
};

Matrix4 operator* (const Matrix4& a, float b);
Matrix4 operator/ (const Matrix4& a, float b);
Matrix4 operator*(const Matrix4& a, const Matrix4& b);
Vector4 operator*(const Matrix4& m, const Vector4& v);
float Determinant(const Matrix4& m);
Matrix4 Inverse(const Matrix4& m);
Matrix4 RotateX(const Matrix4& m, float radian);
Matrix4 RotateY(const Matrix4& m, float radian);
Matrix4 RotateZ(const Matrix4& m, float radian);
Matrix4 Translate(const Matrix4& m, const Vector3& v);
Matrix4 Scale(const Matrix4 m, const Vector3 v);

