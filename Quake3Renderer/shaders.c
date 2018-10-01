#include "shaders.h"

#include <glad/glad.h>

int createShader(char* shadercode, int type, unsigned int* shader)
{
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &shadercode, NULL);
	glCompileShader(*shader);

	int success;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

	return success;
}

int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int* shaderProgram) 
{
	*shaderProgram = glCreateProgram();

	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	return success;
}
