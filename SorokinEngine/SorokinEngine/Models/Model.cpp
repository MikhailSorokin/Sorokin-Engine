#include "Model.h"

Model::Model(bool usingTransparency)
{
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
