#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

//My class includes
#include "Rendering/Window.h"
#include <iostream>
#include "Shaders/Shader.h"
#include "Models/TexturedModel.h"
#include "Rendering/Chunk.h"


int main() {
	//Window must be loaded before gladLoadGLLoader is called!
	Window window(1280, 720, "SirrockinEngine");
	window.create();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	chunk cube_chunk(4, 0, 10);

	/* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
	Shader* chunkShaders = new Shader("Shaders/Vertex/cube_chunk.vert", "Shaders/Fragment/cube_chunk.frag");
	chunkShaders->compileShaders();
	GLuint chunkProgramID = chunkShaders->createProgram();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(chunkProgramID);

	glEnableVertexAttribArray(0);

	glm::vec3 cameraPos = glm::vec3(0.f, 0.f, -3.f);
	glm::vec3 cameraFront = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);
	/* ========================== Renderer (OWN CLASS) ============================== */
	while (!window.closed())
	{
		window.clear();

		glm::mat4 view = glm::mat4(1.0);

		cameraFront.x = sin(glm::radians(window.deltaYaw)) * cos(glm::radians(window.deltaPitch));
		cameraFront.y = sin(glm::radians(window.deltaPitch));
		cameraFront.z = cos(glm::radians(window.deltaYaw)) * cos(glm::radians(window.deltaPitch));

		glm::vec3 FPSFront = glm::vec3(cameraFront.x, 0.f, cameraFront.z);
		cameraPos += window.deltaZ * FPSFront; //FPSFront camera for FPS style, use cameraFront to use flying style camera
		cameraPos += window.deltaX * glm::normalize(glm::cross(cameraFront, cameraUp));

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 proj = glm::perspective(glm::radians(Window::FOV), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);


		/*============================= RENDERING ======================================== */

		float verticesArr[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
				};
		std::vector<float> vertices(std::begin(verticesArr), std::end(verticesArr));

		TexturedModel model1("Textures/container.jpg", vertices);

		model1.init();
		unsigned int textureID1 = model1.getTextureID();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID1);


		// draw first triangle using the data from the first VAO
		chunkShaders->setMatrix4f("view", view);
		chunkShaders->setMatrix4f("projection", proj);

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0, 0, 0));

		chunkShaders->setMatrix4f("model", model);

		glUseProgram(chunkProgramID);

		//Chunk stuff here
		cube_chunk.render();


		/*============================= END RENDERING ======================================== */

		window.update();
	}

	delete(chunkShaders);

	return 0;
}

