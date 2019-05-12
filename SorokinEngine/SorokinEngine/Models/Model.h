#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "../Utilities/Loader.h"

#pragma once

class Model
{
	public:
		Model(bool usingTransparency = false);

	protected:
		bool m_usingTransparency;

	private:
		void specialFunction();

};

