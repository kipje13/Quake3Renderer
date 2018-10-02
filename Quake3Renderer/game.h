#ifndef GAME_H
#define GAME_H

#include <glfw/glfw3.h>



void load();
void start(GLFWwindow* w);
void update(double deltatime);
void resize(GLFWwindow* window, int width, int height);

#endif