#include "game.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "shaders.h"
#include "bsp.h"
#include "bsprenderer.h"

BSP_DATA* bsp;
BSP_RENDEROBJECT* renderobject;

unsigned int shader;

void load()
{
	FILE* f = fopen("G:\\Github\\Quake3Renderer\\Debug\\ct3tourney3.bsp", "rb");

	fseek(f, 0, SEEK_END);
	int filesize = ftell(f);
	rewind(f);

	char* bspdata = (char*)malloc(sizeof(char) * filesize);
	fread(bspdata, sizeof(char), filesize, f);

	fclose(f);

	bsp = loadbsp(bspdata);
}

void start()
{
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

	mat4 p = createPerspective(90, 1280, 720, 1, 10000);
	mat4 t = createTranslation(makeVec3(0, 500, -1000));

	setShaderUniformMatrix4(shader, "projectionview", MultiplyM4(p, t));

	renderobject = setupBsp(bsp);
}

void update(double deltatime)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderBsp(renderobject);
}

void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	mat4 p = createPerspective(90, width, height, 1, 10000);
	mat4 t = createTranslation(makeVec3(0, 500, -1000));

	setShaderUniformMatrix4(shader, "projectionview", MultiplyM4(p, t));
}