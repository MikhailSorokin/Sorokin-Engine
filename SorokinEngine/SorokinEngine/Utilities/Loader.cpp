﻿#include "Loader.h"

unsigned int Loader::currentVAOIndex = 0;

//This method will creat the VAO and the VBOs that will go within each VAO.
void Loader::createAttributes(const std::vector<float>& vertices)
{
	glGenVertexArrays(1, VAOs);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	//0 is the Position Attribute, 8 will be size of the vertices array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	//1 is the U/V texture coordinates Attribute, 8 will be size of the vertices array
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//TODO - Normal coordinateS?
	currentVAOIndex = currentVAOIndex + 1;
}

void Loader::deleteAttribute()
{
	glDeleteVertexArrays(1, &VAOs[0]);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

unsigned int Loader::getVAO(int index)
{
	return VAOs[index];
}


unsigned int Loader::getCurrVAOIndex()
{
	return currentVAOIndex;
}