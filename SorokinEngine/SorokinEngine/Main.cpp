#include <glad/glad.h>
#include <GLFW/glfw3.h>

//My class includes
#include "Rendering/Window.h"
#include <iostream>
#include "Shaders/Shader.h"

char* filetobuf(const char *file);

int main() {
	//Window must be loaded before gladLoadGLLoader is called!
	Window window(1920, 1080, "SirrockinEngine");
	window.create();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	float colors[6][3] = {
		{ 0, 0, 1 },
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 },
		{ 1, 0, 0 },
		{ 0, 1, 0 }
	};

	/* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
	Shader* exampleShader = new Shader("Shaders/simple_triangle.vert", "Shaders/simple_triangle.frag");
	exampleShader->compileShaders();
	GLuint shaderProgramExample = exampleShader->createProgram();

	GLuint VAO, VBO[2], EBO;

	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	glGenVertexArrays(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	/* Copy the vertex data from diamond to our buffer */
	/* 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	/* Enable attribute index 0 as being used */
	glEnableVertexAttribArray(0);

	/* Bind our second VBO as being the active buffer and storing vertex attributes (colors) */
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	/* Copy the vertex data from diamond to our buffer */
	/* 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values */
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	/* Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	/* Enable attribute index 0 as being used */
	glEnableVertexAttribArray(1);

	/* ========================== Renderer (OWN CLASS) ============================== */
	while (!window.closed())
	{
		window.clear();
		/*============================= RENDERING ======================================== */
		glUseProgram(shaderProgramExample);
		glDrawElements(GL_TRIANGLES, 0, 6, indices);
		/*============================= END RENDERING ======================================== */

		window.update();
	}

	delete(exampleShader);
	return 0;
}

