#include <glad/glad.h>
#include <GLFW/glfw3.h>

//My class includes
#include "Rendering/Window.h"
#include <iostream>
#include "Shaders/Shader.h"

char* filetobuf(const char *file);

int main() {
	//Window must be loaded before gladLoadGLLoader is called!
	Window window(1080, 720, "SirrockinEngine");
	window.create();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	float vertices1[] = {
		-0.9f, -0.5f,  // left 
		-0.0f, -0.5f, // right
		-0.45f, 0.5f  // top 
	};
	float colors1[] = {
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f
	};

	float vertices2[] = {
		0.0f, -0.5f,  // left
		0.9f, -0.5f,  // right
		0.45f, 0.5f   // top 
	};
	float colors2[] = {
		1.f, 1.f, 0.f,
		1.f, 1.f, 0.f,
		1.f, 1.f, 0.f
	};

	/* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
	Shader* exampleShader = new Shader("Shaders/opacity_lerp_triangle.vert", "Shaders/opacity_lerp_triangle.frag");
	exampleShader->compileShaders();
	GLuint shaderProgramExample = exampleShader->createProgram();

	unsigned int VAOs[2], VBOs[4];

	//CHALLENGE 1 - 2 Triangles near each other.

	//Model model* = new Model()
	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(2, VAOs);
	glGenBuffers(4, VBOs);

	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAOs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors2), colors2, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float delta, offset = 0.f;
	/* ========================== Renderer (OWN CLASS) ============================== */
	while (!window.closed())
	{
		window.clear();

		delta = glfwGetTime();
		float green = sin(2.f * delta);
		//int vertexColorLocation = glGetUniformLocation(shaderProgramExample, "color");

		offset += delta / 1000.f;

		/*============================= RENDERING ======================================== */
		// draw first triangle using the data from the first VAO
		glUseProgram(shaderProgramExample);
		//glUniform4f(vertexColorLocation, 0.0f, green, 0.0f, 1.f);
		exampleShader->setFloat("deltaOffset", offset);

		glBindVertexArray(VAOs[0]);
		//glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, 0);
		/*============================= END RENDERING ======================================== */

		window.update();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(4, VBOs);

	delete(exampleShader);

	return 0;
}

