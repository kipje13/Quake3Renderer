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

vec4 multiplyV4C(vec4 a, float s)
{
	vec4 v = { a.x * s, a.y * s, a.z * s, a.w * s };
	return v;
}

vec4 multiplyM4V4(mat4 m, vec4 v)
{
	m.column[0] = multiplyV4C(m.column[0], v.x);
	m.column[1] = multiplyV4C(m.column[1], v.y);
	m.column[2] = multiplyV4C(m.column[2], v.z);
	m.column[3] = multiplyV4C(m.column[3], v.w);

	float x = m.column[0].x + m.column[1].x + m.column[2].x + m.column[3].x;
	float y = m.column[0].y + m.column[1].y + m.column[2].y + m.column[3].y;
	float z = m.column[0].z + m.column[1].z + m.column[2].z + m.column[3].z;
	float w = m.column[0].w + m.column[1].w + m.column[2].w + m.column[3].w;

	vec4 r = { x, y, z, w };

	return r;
}

mat4 MultiplyM4(mat4 a, mat4 b)
{
	mat4 m = {
		multiplyM4V4(a, b.column[0]),
		multiplyM4V4(a, b.column[1]),
		multiplyM4V4(a, b.column[2]),
		multiplyM4V4(a, b.column[3])
	};

	return m;
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

vec3 makeVec3(float x, float y, float z)
{
	vec3 v = { x, y, z };
	return v;
}

vec4 makeVec4(float x, float y, float z, float w)
{
	vec4 v = { x, y, z, w };
	return v;
}