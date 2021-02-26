#include "PointLight.h"

PointLight::PointLight(Vector3 position, Vector3 diffuseColor, Vector3 specularColor, float specularPower)
{
	this->position = position;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
	this->specularPower = specularPower;
}

void PointLight::Update()
{
	ImageRenderer* r = ImageRenderer::GetInstance();
	r->SetUniform("lightPosition", position);
	r->SetUniform("diffuseColor", diffuseColor);
	r->SetUniform("specularColor", specularColor);
	r->SetUniform("specularPower", specularPower);
}
