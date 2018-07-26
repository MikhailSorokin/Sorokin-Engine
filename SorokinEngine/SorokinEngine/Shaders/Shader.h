#pragma once

#include <iostream>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const char* vertexSrcPath, const char* destSrcPath);
	char* filetobuf(const char* file);
	virtual ~Shader();

	void compileShaders();
	GLuint createProgram();

protected:
	const GLchar* m_vertexShaderSource;
	const GLchar* m_fragmentShaderSource;

	GLuint m_vertexShader, m_fragmentShader;

};

