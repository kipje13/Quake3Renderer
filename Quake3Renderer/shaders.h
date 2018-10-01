#ifndef SHADERS_H
#define SHADERS_H

int createShader(char* shadercode, int type, unsigned int* shader);
int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int* shaderProgram);

#endif