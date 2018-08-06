#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm/mat4x3.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexSrcPath, const char* destSrcPath);
	char* filetobuf(const char* file);
	virtual ~Shader();

	void compileShaders();
	GLuint createProgram();

	void setFloat(const std::string& name, float value) const;

	void setDouble(const std::string & name, double value) const;

	void setInt(const std::string & name, int value) const;

	void setMatrix4f(const std::string & name, glm::mat4 value) const;

protected:
	const GLchar* m_vertexShaderSource;
	const GLchar* m_fragmentShaderSource;

	GLuint m_vertexShader, m_fragmentShader;
	GLuint m_shaderprogram;
};

