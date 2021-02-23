#pragma once

#include "Graphics.h"
#include <string>

class ShaderProgram
{
private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
	bool initialised = false;


public:
	ShaderProgram();

	ShaderProgram(std::string vertexFilename, std::string fragmentFilename);

	~ShaderProgram();

	void UseProgram();

	GLuint GetUniformLocation(std::string varName);

	static void ClearPrograms();
};

