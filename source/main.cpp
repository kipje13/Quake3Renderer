#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"

#include <stdio.h>
#include <stdlib.h>

double prevTime = 0;

bool fileExists(const char* path);

int main(int argc, char **argv)
{
	if (argc < 2 || !fileExists(argv[1]))
	{
		printf("No file passed or file could not be found.");
		return 0;
	}
	
	char* maptoload = (char*)malloc((strlen(argv[1]) + 1) * sizeof(char));
	strcpy(maptoload, argv[1]);

	load(maptoload);

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

bool fileExists(const char* path) 
{
	if (FILE *file = fopen(path, "r")) 
	{
		fclose(file);
		return true;
	}
	else 
	{
		return false;
	}
}