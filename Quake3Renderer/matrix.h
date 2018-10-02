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

vec4 operator *(vec4 v, float s);
vec4 operator *(mat4 m, vec4 v);
mat4 operator *(mat4 a, mat4 b);


float dot(vec3 a, vec3 b);
float length(vec3 v);
float lengthSquared(vec3 v);


#endif
