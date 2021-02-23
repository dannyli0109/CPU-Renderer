#pragma once

#include <string>
#include "Matrix4.h"
#include "Graphics.h"
#include <vector>
#include <queue>
//#include "Mesh.h"
#include "Vector3.h"
#include "Vector2.h"

std::string LoadFileAsString(std::string filename);
Matrix4 GetViewMatrix(const Vector3& eyePos, const Vector3& center, const Vector3& up);
Matrix4 GetViewportMatrix(int l, int r, int b, int t);
Matrix4 GetOrthoProjectionMatrix(float l, float r, float b, float t, float n, float f);
Matrix4 GetPerspProjectionMatrix(float fovY, float aspect, float near, float far);
void OnWindowResized(GLFWwindow* window, int newWidth, int newHeight);
std::vector<std::string> Split(const std::string& s, std::string delimiter);
void ParseObj(
	std::string filename, 
	std::vector<Vector3>& verts, std::vector<unsigned short>& vertIndices, 
	std::vector<Vector2>& uvs, std::vector<unsigned short>& uvIndices,
	std::vector<Vector3>& normals, std::vector<unsigned short>& normalIndices,
	bool flipUV
);