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
#include "Rendering/chunk.h"


int main() {
	//Window must be loaded before gladLoadGLLoader is called!
	Window window(1080, 720, "SirrockinEngine");
	window.create();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	
	/* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
	auto chunkShaders = std::make_unique<Shader>("Shaders/Vertex/chunk.vert", "Shaders/Fragment/chunk.frag");
	chunkShaders->compileShaders();
	GLuint shaderProgramID = chunkShaders->createProgram();
	
	TexturedModel chunkModel("Textures/container.jpg");

	chunkModel.init();
	unsigned int textureID = chunkModel.getTextureID();

	chunk bigChunk;

	glUseProgram(shaderProgramID);
	chunkShaders->setInt("ourTexture", 0);

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
		cameraPos += window.deltaZ * cameraFront; //FPSFront camera for FPS style, use cameraFront to use flying style camera
		cameraPos += window.deltaX * glm::normalize(glm::cross(cameraFront, cameraUp));

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 proj = glm::perspective(glm::radians(Window::FOV), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);


		/*============================= RENDERING ======================================== */


		// draw first triangle using the data from the first VAO

		chunkShaders->setMatrix4f("view", view);
		chunkShaders->setMatrix4f("projection", proj);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glUseProgram(shaderProgramID);

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0,0,0));
		
		chunkShaders->setMatrix4f("model", model);

		glBindVertexArray(bigChunk.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, bigChunk.getTriangleCount());

		/*============================= END RENDERING ======================================== */

		window.update();
	}

	return 0;
}

