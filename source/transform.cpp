#include "transform.h"

#include "matrix.h"

Transform::Transform()
{
	pos = vec3{ 0, 0, 0 };
	rot = identityMatrix();
}

void Transform::translateLocal(vec3 v)
{
	vec4 n = rot * vec4{ v.x, v.y, v.z, 1 };
	pos = pos + vec3{n.x, n.y, n.z};
}

void Transform::translateWorld(vec3 v)
{
	pos = pos + v;
}

void Transform::rotate(vec3 v)
{
	rot = createRotationX(v.x) * createRotationY(v.y) * createRotationZ(v.z);
}

mat4 Transform::getMatrix()
{
	return createTranslation(pos) * rot;
}