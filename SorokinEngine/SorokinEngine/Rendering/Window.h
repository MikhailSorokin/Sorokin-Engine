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

		int getWidth();
		int getHeight();

		//TODO - Move into own class
		float deltaX;
		float deltaZ;

		static float deltaYaw;
		static float deltaPitch;

		static float deltaTime;
		static float lastTime;

		static float FOV;


		GLFWwindow* m_window;

	protected:
		int m_width;
		int m_height;

		static float lastX;
		static float lastY;
		static bool bSetup;

		static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xPos, double yPos);

		const char* m_name;

		double blendValue;
};