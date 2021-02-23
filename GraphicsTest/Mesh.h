#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <vector>
#include "ImageRenderer.h"
#include "Utilities.h"

/*
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 vertTangent;
	glm::vec3 vertBitangent;
	glm::vec3 color;
	glm::vec2 uv;
*/
//class ImageRenderer;
class ImageRenderer;

struct Vertex
{
	Vector3 position{0, 0, 0};
	Vector3 normal{ 0, 0, 0 };
	Vector3 vertTangent{ 0, 0, 0 };
	Vector3 vertBitangent{ 0, 0, 0 };
	Vector4 color{ 1, 1, 1, 1 };
	Vector2 uv{ 0,0 };
};

class Mesh
{
public:
	Mesh(std::string fileName);
	void Bind();
	static void Unbind();
	void Update();
	void Draw();
	unsigned int vertexId;
	unsigned int indexId;
};

