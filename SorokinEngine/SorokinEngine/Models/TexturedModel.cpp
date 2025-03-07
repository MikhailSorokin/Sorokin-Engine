﻿#include "TexturedModel.h"


TexturedModel::TexturedModel(const char* inPath, const std::vector<float>& vertices, const std::vector<int>& indices, bool usingTransparency) : Model(vertices, indices, usingTransparency)
{
	m_Path = inPath;
}

TexturedModel::TexturedModel(const char* inPath, const std::vector<float>& vertices, bool usingTransparency) : Model(vertices, usingTransparency)
{
	m_Path = inPath;
}

void TexturedModel::init()
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	m_texture = texture;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(m_Path, &width, &height, &nrChannels, 0);

	if (data)
	{	
		if (m_usingTransparency) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		} else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

unsigned int TexturedModel::getTextureID()
{
	return m_texture;
}