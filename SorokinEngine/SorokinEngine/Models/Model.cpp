#include "Model.h"

Model::Model(const std::vector<float>& vertices, const std::vector<int>& indices) : m_loader(vertices, indices)
{
	m_vertices = vertices;
	m_indices = indices;
}

//Does something crazy with vertex and fragment shaders.
void Model::specialFunction()
{
	float delta, offset = 0.f;

	delta = glfwGetTime();
	float green = sin(2.f * delta);
	//int vertexColorLocation = glGetUniformLocation(shaderProgramExample, "color");

	offset += delta / 1000.f;
}