#include "Triangle.h"

Triangle::Triangle(Vector3 p1, Vector3 p2, Vector3 p3)
{
	vertices[0] = p1;
	vertices[1] = p2;
	vertices[2] = p3;
}

Vector3& Triangle::operator[](int i)
{
	return vertices[i];
}

const Vector3& Triangle::operator[](int i) const
{
	return vertices[i];
}
