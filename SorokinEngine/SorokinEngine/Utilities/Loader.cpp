#include "Loader.h"
#include <glad/glad.h>

Loader::Loader(const std::vector<float>& vertices, const std::vector<int>& indices)
{
	createAttributes(vertices, indices);
}

//This method will creat the VAO and the VBOs that will go within each VAO.
void Loader::createAttributes(const std::vector<float>& vertices, const std::vector<int>& indices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBOs);
	glGenBuffers(1, &EBO);

	for (int i = 0; i < 3; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
	}
	glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

	//0 is the Position Attribute, 8 will be size of the vertices array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	//1 is the Color Attribute, 8 will be size of the vertices array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//2 is the U/V texture coordinates Attribute, 8 will be size of the vertices array
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//TODO - Normal coordinateS?

}

void Loader::bindVAO(int VAO)
{
	glBindVertexArray(VAO);
}

void Loader::deleteAttribute()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBOs);
	glDeleteBuffers(1, &EBO);
}

unsigned int Loader::getVAO()
{
	return VAO;
}
