#include "Model.h"
#include "../Utilities/stb_image.h"

#pragma once

class TexturedModel : Model
{
	public:
		TexturedModel(const char* inPath, const std::vector<float>& vertices, const std::vector<int>& indices);
		void init();
		unsigned int getTextureID();
		unsigned int getCurrentVAO();
		void cleanUp();

protected:
		const char* m_Path;
		unsigned char m_texture;
};
