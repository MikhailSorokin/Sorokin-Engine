#include "Window.h"
#include <iostream>
#include <algorithm>


//Called whenever the window is resized with the mouse or other inputs
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(const int width, const int height, const char* name)
{
	m_width = width;
	m_height = height;
	m_name = name;

	blendValue = 1.f;
}

Window::~Window()
{
	glfwTerminate();
}

void Window::create()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, m_name, nullptr, nullptr);
	if (!m_window) {
		std::cout << "Terminating the windows." << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_window);

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, m_width, m_height);
}

bool Window::closed()
{
	return glfwWindowShouldClose(m_window);
}

void Window::update()
{
	//TODO - Make input own class?
	processInput(m_window);
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		blendValue += (0.01f);
		blendValue = std::min(blendValue, 1.0);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		blendValue -= (0.01f);
		blendValue = std::max(blendValue, 0.0);
	}
}

void Window::clear()
{
	//Have to clear the buffer bit so that we refresh rendering the graphics every frame
	glClearColor(0, 0.2f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float Window::getUpdatingOpacityChange()
{
	return blendValue;
}

int Window::getWidth()
{
	return m_width;
}

int Window::getHeight()
{
	return m_width;
}
