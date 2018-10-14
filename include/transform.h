#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"

class Transform
{
private: 
	vec3 pos;
	mat4 rot;

public:
	Transform();
	void translateLocal(vec3 v);
	void translateWorld(vec3 v);
	
	void rotate(vec3 v);

	mat4 getMatrix();
};

#endif

