#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "../Utilities/Loader.h"

#pragma once

class Model
{
	public:
		Model(const std::vector<float>& vertices, const std::vector<int>& indices, bool usingTransparency = false);

		Model(const std::vector<float>& vertices, bool usingTransparency = false);

	protected:
		std::vector<float> m_vertices;
		std::vector<int> m_indices;
		bool m_usingTransparency;

	private:
		void specialFunction();

};

