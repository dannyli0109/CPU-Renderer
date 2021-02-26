#pragma once
#include "vector3.h"
#include "ImageRenderer.h"

class PointLight
{
public:
	PointLight(Vector3 position, Vector3 diffuseColor, Vector3 specularColor, float specularPower);
	void Update();

private:
	Vector3 position;
	Vector3 diffuseColor;
	Vector3 specularColor;
	float specularPower;
};

