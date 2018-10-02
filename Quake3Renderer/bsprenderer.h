#ifndef BSPRENDERER_H
#define BSPRENDERER_H

#include "bsp.h"

typedef struct {
	BSP_DATA* data;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	BSP_FACE** renderqueue;
	unsigned int* lightmaps;
} BSP_RENDEROBJECT;

BSP_RENDEROBJECT* setupBsp(BSP_DATA* bsp);
void renderBsp(BSP_RENDEROBJECT* renderobject);

#endif 



