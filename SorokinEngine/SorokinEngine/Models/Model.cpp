#include "Model.h"

Model::Model(const std::vector<float>& vertices, const std::vector<int>& indices, bool usingTransparency)
{
	m_vertices = vertices;
	m_indices = indices;
	m_usingTransparency = usingTransparency;
}

Model::Model(const std::vector<float>& vertices, bool usingTransparency)
{
	m_vertices = vertices;
	m_usingTransparency = usingTransparency;
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
