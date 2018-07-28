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
		0.5f,  0.5f, 
		0.5f, -0.5f,  
		-0.5f, -0.5f,
		-0.5f, 0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	/* ============================ LOAD the SHADERS here (to be loaded in their own class) ==================================== */
	Shader* exampleShader = new Shader("Shaders/simple_triangle.vert", "Shaders/simple_triangle.frag");
	exampleShader->compileShaders();
	GLuint shaderProgramExample = exampleShader->createProgram();

	unsigned int VAO, VBO, EBO;


	//Model model* = new Model()
	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	/* ========================== Renderer (OWN CLASS) ============================== */
	while (!window.closed())
	{
		window.clear();
		/*============================= RENDERING ======================================== */
		glUseProgram(shaderProgramExample);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
		/*============================= END RENDERING ======================================== */

		window.update();
	}

	delete(exampleShader);


	return 0;
}

