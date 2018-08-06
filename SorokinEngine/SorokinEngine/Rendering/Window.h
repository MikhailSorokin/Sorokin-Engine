#pragma once

#include <GLFW/glfw3.h>

/* ===================== WINDOW (To be in its own class) ================ */
class Window {
	public:
		Window(int width, int height, const char* name);
		~Window();

		void create();
		bool closed();
		void update();
		void processInput(GLFWwindow * window);
		void clear();

		float getUpdatingOpacityChange();

	protected:
		int m_width;
		int m_height;

		const char* m_name;

		GLFWwindow* m_window;
		double blendValue;
};