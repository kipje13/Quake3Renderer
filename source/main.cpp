#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game.h>

#include <stdio.h>
#include <stdlib.h>

double prevTime = 0;

int main()
{
	load();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "test", NULL, NULL);

	if (window == NULL)
	{
		printf("Failed to create window!\n");
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD!\n");
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, resize);

	start(window);

	while (!glfwWindowShouldClose(window))
	{
		double delta = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();

		update(delta);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}