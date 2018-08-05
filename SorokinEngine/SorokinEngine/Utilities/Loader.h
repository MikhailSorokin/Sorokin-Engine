#pragma once
#include <vector>

class Loader
{
	public:
		Loader(const std::vector<float>& vertices, const std::vector<int>& indices);
		void createAttributes(const std::vector<float>& vertices, const std::vector<int>& indices);
		void bindVAO(int VAO);
		void deleteAttribute();

		unsigned int getVAO();

	private:
		//TODO - Change later to include a lot of objects
		unsigned int VBOs[3];
		unsigned int VAO, EBO;

};
