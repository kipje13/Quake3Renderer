#include "matrix.h"

#include <math.h>

/// TODO: This is a mess

mat4 identityMatrix()
{
	mat4 i = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	return i;
}

mat4 createTranslation(vec3 translation)
{
	mat4 m = identityMatrix();

	m.column[3].x = translation.x;
	m.column[3].y = translation.y;
	m.column[3].z = translation.z;

	return m;
}

mat4 createScale(vec3 scale)
{
	mat4 m = identityMatrix();

	m.column[0].x = scale.x;
	m.column[1].y = scale.y;
	m.column[2].z = scale.z;

	return m;
}

/*mat4 createScale(float scale)
{
	mat4 m = identityMatrix;

	m.column[0].x = scale;
	m.column[1].y = scale;
	m.column[2].z = scale;

	return m;
}*/

mat4 createRotationX(float angle)
{
	mat4 m = identityMatrix();

	m.column[1].y = cos(angle);
	m.column[1].z = sin(angle);
	m.column[2].y = -sin(angle);
	m.column[2].z = cos(angle);

	return m;
}

mat4 createRotationY(float angle)
{
	mat4 m = identityMatrix();

	m.column[0].x = cos(angle);
	m.column[2].x = sin(angle);
	m.column[0].z = -sin(angle);
	m.column[2].z = cos(angle);

	return m;
}
mat4 createRotationZ(float angle)
{
	mat4 m = identityMatrix();

	m.column[0].x = cos(angle);
	m.column[0].y = sin(angle);
	m.column[1].x = -sin(angle);
	m.column[1].y = cos(angle);

	return m;
}

mat4 createPerspective(float fov, int width, int height, float znear, float zfar)
{
	float top = tan(fov / 2) * znear;
	float right = top * ((float)width / height);

	float s1 = (2 * znear) / right;
	float s2 = (2 * znear) / top;
	float a = -(zfar + znear) / ((zfar - znear));
	float b = -(2 * zfar * znear) / ((zfar - znear));

	mat4 m = {
		s1, 0, 0, 0,
		0,s2, 0, 0,
		0, 0, a,-1,
		0, 0, b, 0
	};

	return m;
}

mat4 transpose(mat4 m)
{
	mat4 r;

	r.column[0].x = m.column[0].x;
	r.column[0].y = m.column[1].x;
	r.column[0].z = m.column[2].x;
	r.column[0].w = m.column[3].x;

	r.column[1].x = m.column[0].y;
	r.column[1].y = m.column[1].y;
	r.column[1].z = m.column[2].y;
	r.column[1].w = m.column[3].y;

	r.column[2].x = m.column[0].z;
	r.column[2].y = m.column[1].z;
	r.column[2].z = m.column[2].z;
	r.column[2].w = m.column[3].z;

	r.column[3].x = m.column[0].w;
	r.column[3].y = m.column[1].w;
	r.column[3].z = m.column[2].w;
	r.column[3].w = m.column[3].w;

	return r;
}


vec4 operator*(vec4 v, float s)
{
	vec4 r = { v.x * s, v.y * s, v.z * s, v.w * s };
	return r;
}

vec4 operator*(mat4 m, vec4 v)
{
	m.column[0] = m.column[0] * v.x;
	m.column[1] = m.column[1] * v.y;
	m.column[2] = m.column[2] * v.z;
	m.column[3] = m.column[3] * v.w;

	float x = m.column[0].x + m.column[1].x + m.column[2].x + m.column[3].x;
	float y = m.column[0].y + m.column[1].y + m.column[2].y + m.column[3].y;
	float z = m.column[0].z + m.column[1].z + m.column[2].z + m.column[3].z;
	float w = m.column[0].w + m.column[1].w + m.column[2].w + m.column[3].w;

	vec4 r = { x, y, z, w };

	return r;
}

mat4 operator*(mat4 a, mat4 b)
{
	mat4 m = {
		a * b.column[0],
		a * b.column[1],
		a * b.column[2],
		a * b.column[3]
	};

	return m;
}

vec3 operator +(vec3 a, vec3 b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

float dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length(vec3 v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float lengthSquared(vec3 v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}