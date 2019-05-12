#include "Window.h"
#include <iostream>
#include <algorithm>

float Window::lastX = 0.f;
float Window::lastY = 0.f;
float Window::deltaPitch = 0.f;
float Window::deltaYaw = 0.f;

float Window::deltaTime = 0.f;
float Window::lastTime = 0.f;

float Window::FOV = 45.f;

float Window::keyboardSpeed = 25.f;

bool Window::bSetup = false;

//Called whenever the window is resized with the mouse or other inputs
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(const int width, const int height, const char* name)
{
	m_width = width;
	m_height = height;
	m_name = name;

	lastX = width / 2;
	lastY = height / 2;

	blendValue = 0.5f;
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
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(m_window, &Window::mouse_callback);
	glfwSetScrollCallback(m_window, &Window::scroll_callback);

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


	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	float cameraSpeed = keyboardSpeed * deltaTime;
	deltaZ = 0.f;
	deltaX = 0.f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		deltaZ = cameraSpeed;
	} if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		deltaZ = -cameraSpeed;
	} if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		deltaX = -cameraSpeed;
	} if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		deltaX = cameraSpeed;
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

void Window::mouse_callback(GLFWwindow * window, double xPos, double yPos)
{
	if (!bSetup) {
		lastX = xPos;
		lastY = yPos;
		bSetup = true;
	}

	float offsetX = lastX - xPos;
	float offsetY = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	float sensitivity = 0.009f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	deltaYaw += offsetX;
	deltaPitch += offsetY;

	if (deltaPitch > 89.0f)
		deltaPitch = 89.0f;
	if (deltaPitch < -89.0f)
		deltaPitch = -89.0f;
}

void Window::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	if (FOV >= 1.0f && FOV <= 45.0f)
		FOV -= yoffset;
	if (FOV <= 1.0f)
		FOV = 1.0f;
	if (FOV >= 45.0f)
		FOV = 45.0f;
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
