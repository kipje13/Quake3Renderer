#include "game.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "shaders.h"
#include "bsp.h"
#include "bsprenderer.h"
#include "matrix.h"
#include "transform.h"

GLFWwindow* window;

BSP_DATA* bsp;
BspRenderer* bspRenderer;

unsigned int shader;

mat4 projectionmatrix;
mat4 quake3matrix = { vec4{0, 0, -1, 0}, vec4{ -1, 0, 0, 0 }, vec4{ 0, 1, 0, 0 }, vec4{ 0, 0, 0, 1 } };

vec3 campos = vec3{ 1000, 0, 0 };

Transform* camera;

void input();

void load(char* mapfile)
{
	FILE* f = fopen(mapfile, "rb");

	fseek(f, 0, SEEK_END);
	int filesize = ftell(f);
	rewind(f);

	char* bspdata = (char*)malloc(sizeof(char) * filesize);
	fread(bspdata, sizeof(char), filesize, f);

	fclose(f);

	bspRenderer = new BspRenderer(loadbsp(bspdata));
}

void start(GLFWwindow* w)
{
	camera = new Transform();

	window = w;

	glEnable(GL_DEPTH_TEST);

	char* vertex =
		"#version 430 core\n\
		layout(location = 0) in vec3 aPos;\n\
		layout(location = 1) in vec2 aTexCoord;\n\
		layout(location = 2) in vec2 aLMTexCoord;\n\
		layout(location = 3) in vec3 aNormal;\n\
		layout(location = 4) in vec4 aColor;\n\
		\n\
		out vec3 oPos;\n\
		out vec2 oTexCoord;\n\
		out vec2 oLMTexCoord;\n\
		out vec3 oNormal;\n\
		out vec4 oColor;\n\
		\n\
		uniform mat4 projectionview;\
		\n\
		void main()\n\
		{\n\
			gl_Position = projectionview * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n\
			oPos = aPos;\n\
			oTexCoord = aTexCoord;\n\
			oLMTexCoord = aLMTexCoord;\n\
			oNormal = aNormal;\n\
			oColor = aColor;\n\
		}";

	char* fragment =
		"#version 430 core\n\
		in vec3 oPos;\n\
		in vec2 oTexCoord;\n\
		in vec2 oLMTexCoord;\n\
		in vec3 oNormal;\n\
		in vec4 oColor;\n\
		\n\
		uniform sampler2D lightmap;\n\
		\n\
		out vec4 FragColor;\n\
		\n\
		void main()\n\
		{\n\
			FragColor = texture(lightmap, oLMTexCoord);\n\
		}";

	unsigned int vs, fs;

	if (!createShader(vertex, GL_VERTEX_SHADER, &vs))
	{
		char infoLog[512];
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	if (!createShader(fragment, GL_FRAGMENT_SHADER, &fs))
	{
		char infoLog[512];
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	if (!createShaderProgram(vs, fs, &shader))
	{
		char infoLog[512];
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	glUseProgram(shader);

	projectionmatrix = createPerspective(90, 1280, 720, 1, 10000) * quake3matrix;

	

	bspRenderer->setupBsp();
}

void update(double deltatime)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	input();

	setShaderUniformMatrix4(shader, "projectionview", projectionmatrix * camera->getMatrix());

	bspRenderer->renderBsp();
}

void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	projectionmatrix = createPerspective(90, width, height, 1, 10000) * quake3matrix;
}

void input()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->translateLocal(vec3{ -10, 0, 0 });
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->translateLocal(vec3{ 10, 0, 0 });
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->translateLocal(vec3{ 0, -10, 0 });
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->translateLocal(vec3{ 0, 10, 0 });
	}
}