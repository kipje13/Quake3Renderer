#ifndef BSPRENDERER_H
#define BSPRENDERER_H

#include "bsp.h"

class BspRenderer
{
private:
	BSP_DATA* data;
	unsigned int VBO, VAO, EBO;
	BSP_FACE** renderqueue;
	unsigned int* lightmaps;

	void generateLightmaps();

public:
	BspRenderer(BSP_DATA* bsp);
	void setupBsp();
	void renderBsp();
};

#endif 



