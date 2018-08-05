#include <glad/glad.h>
#include <GLFW/glfw3.h>

//My class includes
#include "Rendering/Window.h"
#include <iostream>
#include "Shaders/Shader.h"
#include "Models/TexturedModel.h"

int main() {
	//Window must be loaded before gladLoadGLLoader is called!
	Window window(1080, 720, "SirrockinEngine");
	window.create();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	float verticesArr[] = {
		//position			//color          //texture
		-0.5f, 0.5f, 0.f,	0.f, 1.f, 0.f,   0.f, 0.f,
		0.5f, 0.5f, 0.f,	0.f, 1.f, 0.f,	 1.f, 0.f,
		0.5f, -0.5f, 0.f,	0.f, 1.f, 0.f,	 1.f, 1.f,
		-0.5f, -0.5f, 0.f,	0.f, 1.f, 0.f,	 0.f, 1.f
	};

	int indicesArr[] = {
		0, 2, 3,
		0, 1, 2
	};

	std::vector<float> vertices(std::begin(verticesArr), std::end(verticesArr));
	std::vector<int> indices(std::begin(indicesArr), std::end(indicesArr));

	TexturedModel texturedModel("Textures/dank.png", vertices, indices);
	texturedModel.init();
	unsigned int textureID = texturedModel.getTextureID();
	unsigned int VAO = texturedModel.getCurrentVAO();

	/* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
	Shader* exampleShader = new Shader("Shaders/Vertex/simple_quad.vert", "Shaders/Fragment/simple_quad.frag");
	exampleShader->compileShaders();
	GLuint shaderProgramExample = exampleShader->createProgram();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/* ========================== Renderer (OWN CLASS) ============================== */
	while (!window.closed())
	{
		window.clear();

		/*============================= RENDERING ======================================== */
		// draw first triangle using the data from the first VAO
		glUseProgram(shaderProgramExample);

		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/*============================= END RENDERING ======================================== */

		window.update();
	}

	delete(exampleShader);
	texturedModel.cleanUp();

	return 0;
}

