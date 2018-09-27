#include "game.h"

#include <glfw/glfw3.h>

#include <stdio.h>

#include "bsp.h"

BSP* bsp;

double x = 0;

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

}

void update(double deltatime)
{
	x += deltatime;
	if (x > 1)
		x = 0;

	glClearColor(x, x, x, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void resize(GLFWwindow* window, int width, int height)
{
	
}