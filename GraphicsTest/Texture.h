#pragma once
#include <string>
#include "ImageRenderer.h"

class Texture
{
public:
	Texture(std::string fileName);
	void Bind(int textureUnit);
	static void Unbind();

private:
	unsigned int textureId;
};

