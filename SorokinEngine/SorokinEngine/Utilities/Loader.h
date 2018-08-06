#pragma once
#include <vector>
#include <glad/glad.h>
#include <iostream>

class Loader
{
	public:
		void createAttributes(const std::vector<float>& vertices, const std::vector<int>& indices);
		void bindVAO(int VAO);
		void deleteAttribute();

		unsigned int getVAO(int index);

		unsigned int getCurrVAOIndex();

	private:
		//TODO - Change later to include a lot of objects
		unsigned int VAOs[1], EBO, VBO;
		static unsigned int currentVAOIndex;
};
