#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   0.f, 1.0f, 0.0f,	  1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,	  1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indicesArr[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	std::vector<float> vertices(std::begin(verticesArr), std::end(verticesArr));
	std::vector<int> indices(std::begin(indicesArr), std::end(indicesArr));

	Loader loader;
	loader.createAttributes(vertices, indices);

	TexturedModel model1("Textures/container.jpg", vertices, indices);
	TexturedModel model2("Textures/awesomeFace.png", vertices, indices, true);

	/* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
	Shader* exampleShader = new Shader("Shaders/Vertex/simple_quad.vert", "Shaders/Fragment/simple_quad.frag");
	exampleShader->compileShaders();
	GLuint shaderProgramExampleID = exampleShader->createProgram();
	
	model1.init();
	unsigned int textureID1 = model1.getTextureID();

	model2.init();
	unsigned int textureID2 = model2.getTextureID();

	unsigned int VAO = loader.getVAO(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgramExampleID);
	exampleShader->setInt("ourTexture1", 0);
	exampleShader->setInt("ourTexture2", 1);


	/* ========================== Renderer (OWN CLASS) ============================== */
	while (!window.closed())
	{
		window.clear();


		glm::mat4 trans = glm::mat4(1.0); //HAVE TO DO THIS OR ELSE NOT INITIALIZED PROPERLY!!!
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		/*============================= RENDERING ======================================== */
		// draw first triangle using the data from the first VAO

		exampleShader->setFloat("blendValue", window.getUpdatingOpacityChange());
		exampleShader->setMatrix4f("transform", trans);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureID2);


		glUseProgram(shaderProgramExampleID);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/*============================= END RENDERING ======================================== */

		window.update();
	}

	delete(exampleShader);
	loader.deleteAttribute();

	return 0;
}

