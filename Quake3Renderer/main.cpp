#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

double prevTime = 0;

int main()
{
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

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		double delta = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();

		printf("%lf fps\n", 1/delta);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}