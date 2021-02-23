#pragma once
#include "Graphics.h"
#include "ShaderProgram.h"
#include "ImageRenderer.h"
#include "Texture.h"

#include <vector>
#include "Utilities.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define PIXEL_SCALE 1

class Mesh;

class ProgramManager
{

private:
	GLFWwindow* window = nullptr;
	ShaderProgram* simpleShader = nullptr;

	int mouseX = 0;
	int mouseY = 0;
	bool mouseLeftDown = false;
	bool mouseRightDown = false;

	void UpdateMouseState();

public:
	bool Initialise();
	void Run();
	void ShutDown();
	std::vector<Mesh*> meshes;
	Texture* diffuseTexture = nullptr;

private:
	void Draw();
};