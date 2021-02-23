#pragma once
#include "Vector3.h"
struct Triangle
{
public:
	Triangle(Vector3 p1, Vector3 p2, Vector3 p3);
	Vector3& operator[](int i);
	const Vector3& operator[](int i) const;
private:
	Vector3 vertices[3];
};

