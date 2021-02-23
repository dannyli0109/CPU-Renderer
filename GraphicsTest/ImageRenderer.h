#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "Graphics.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Utilities.h"

class ShaderProgram;
struct Vertex;
struct Image
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class ImageRenderer
{
public:
	static ImageRenderer* GetInstance();
	static ImageRenderer* CreateInstance(int width, int height);
	ImageRenderer(const ImageRenderer& other) = delete;
	ImageRenderer& operator=(const ImageRenderer& other) = delete;
	static void DeleteInstance();

	void BindVertex(unsigned int id);
	void BindIndex(unsigned int id);
	void BindTexture(unsigned int id);
	void UnbindVertex();
	void UnbindIndex();
	void UnbindTexture();

	unsigned int GetNextId();
	unsigned int UploadVertexData(const std::vector<Vertex>& vertexData);
	unsigned int UploadIndexData(const std::vector<unsigned short>& indexData);
	unsigned int UploadTexture(const unsigned char* data, int& width, int& height, int& channels);
	void ActiveTexture(int textureUnit);
	Vector4 TextureLookup(const std::vector<std::vector<unsigned char>>& texture, float u, float v);
	Vector4 GetTexturePixel(const std::vector<std::vector<unsigned char>>& texture, int i, int j);

	void SetUniform(std::string s, Matrix4 m);
	void SetUniform(std::string s, int i);
	void SetPixel(int x, int y, float red, float green, float blue);
	void SetSize(int width, int height);

	void DrawImage(ShaderProgram* shader);
	void Draw();
	void DrawLine(Vector3 p1, Vector3 p2, Vector4 color);
	void PupulateTexture();
	double* BaryCentric(float x, float y, Vector3 p0, Vector3 p1, Vector3 p2);
	void DrawTriangle(Vector4 p1, Vector4 p2, Vector4 p3, Vector2 uv1, Vector2 uv2, Vector2 uv3);
	bool InsideTriangle(float x, float y, Vector3 p1, Vector3 p2, Vector3 p3);

	void Clear();

	int GetWidth();
	int GetHeight();
	
private:
	~ImageRenderer();
	ImageRenderer(int width, int height);
	void CreateImage();
	void CreateQuad();

private:
	static ImageRenderer* instance;
	GLuint textureID;
	GLuint quadBuffer;
	int w;
	int h;
	unsigned int activeVertex = 0;
	unsigned int activeIndex = 0;
	unsigned int activeTexture = 0;
	unsigned int bufferCount = 0;
	std::vector<Vector3> image;
	std::vector<Vector3> frameBuffer;
	std::vector<double> depthBuffer;
	Vector4 clearColor = { 0, 0, 0, 1 };

	std::map<unsigned int, std::vector<Vector3>> positions;
	std::map<unsigned int, std::vector<Vector3>> normals;
	std::map<unsigned int, std::vector<Vector3>> vertTangents;
	std::map<unsigned int, std::vector<Vector3>> vertBitangents;
	std::map<unsigned int, std::vector<Vector4>> colors;
	std::map<unsigned int, std::vector<Vector2>> uvs;
	std::map<unsigned int, std::vector<unsigned short>> indices;
	std::map<unsigned int, std::vector<std::vector<unsigned char>>> textures;
	
	std::map<int, unsigned int> textureUnits;
	//std::vector<unsigned short> 

	std::map<std::string, Matrix4> uniformM4;
	std::map<std::string, int> uniformI1;


};


