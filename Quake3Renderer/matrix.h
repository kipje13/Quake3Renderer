#ifndef MATRIX_H
#define MATRIX_H

struct vec3
{
	float x;
	float y;
	float z;
};

struct vec4
{
	float x;
	float y;
	float z;
	float w;
};

struct mat4
{
	vec4 column[4];
};

mat4 identityMatrix();

mat4 createTranslation(vec3 translation);
mat4 createScale(vec3 scale);
mat4 createRotationX(float angle);
mat4 createRotationY(float angle);
mat4 createRotationZ(float angle);

mat4 createPerspective(float fov, int width, int height, float znear, float zfar);

vec4 multiplyV4C(vec4 a, float b);
vec4 multiplyM4V4(mat4 m, vec4 v);
mat4 MultiplyM4(mat4 a, mat4 b);

float dot(vec3 a, vec3 b);
float length(vec3 v);
float lengthSquared(vec3 v);

vec3 makeVec3(float x, float y, float z);
vec4 makeVec4(float x, float y, float z, float w);

#endif
