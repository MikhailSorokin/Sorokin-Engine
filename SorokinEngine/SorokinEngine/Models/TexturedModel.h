#include "Model.h"
#include "../Utilities/stb_image.h"

#pragma once

class TexturedModel : public Model
{
	public:
		TexturedModel(const char * inPath, bool usingTransparency = false);
		void init();
		unsigned int getTextureID();

	protected:
		const char* m_Path;
		unsigned char m_texture;
};
