#ifndef SHADERS_H
#define SHADERS_H

#include "matrix.h"

int createShader(char* shadercode, int type, unsigned int* shader);
int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int* shaderProgram);

void setShaderUniformMatrix4(unsigned int* shaderProgram, char* name, mat4 matrix);

#endif