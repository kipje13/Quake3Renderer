#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int createwindow(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	return window != NULL;
}

void setvsync(int enable)
{
	if (enable == VSYNC_ON)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}