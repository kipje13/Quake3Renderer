#include "bsp.h"

#include <stdlib.h>
#include <string.h>

#define LUMPCOUNT 17

typedef struct 
{
	int offset;
	int length;
} BSP_LUMP;

BSP_DATA* loadbsp(char* data)
{
	BSP_LUMP* lumps;

	BSP_DATA* bsp = (BSP_DATA*)malloc(sizeof(BSP_DATA));

	if (memcmp(data, "IBSP", 4) != 0)
		return NULL;

	lumps = (BSP_LUMP*)(data + 8);

	bsp->entities = (char*)(data + lumps[0].offset);

	bsp->textures = (BSP_TEXTURE*)(data + lumps[1].offset);
	bsp->n_textures = lumps[1].length / sizeof(BSP_TEXTURE);

	bsp->planes = (BSP_PLANE*)(data + lumps[2].offset);
	bsp->n_planes = lumps[2].length / sizeof(BSP_PLANE);

	bsp->nodes = (BSP_NODE*)(data + lumps[3].offset);
	bsp->n_nodes = lumps[3].length / sizeof(BSP_NODE);

	bsp->leaves = (BSP_LEAF*)(data + lumps[4].offset);
	bsp->n_leaves = lumps[4].length / sizeof(BSP_LEAF);

	bsp->leaffaces = (BSP_LEAFFACE*)(data + lumps[5].offset);
	bsp->n_leaffaces = lumps[5].length / sizeof(BSP_LEAFFACE);

	bsp->leafbrushes = (BSP_LEAFBRUSH*)(data + lumps[6].offset);
	bsp->n_leafbrushes = lumps[6].length / sizeof(BSP_LEAFBRUSH);

	bsp->models = (BSP_MODEL*)(data + lumps[7].offset);
	bsp->n_models = lumps[7].length / sizeof(BSP_MODEL);

	bsp->brushes = (BSP_BRUSH*)(data + lumps[8].offset);
	bsp->n_brushes = lumps[8].length / sizeof(BSP_BRUSH);

	bsp->brushsides = (BSP_BRUSHSIDE*)(data + lumps[9].offset);
	bsp->n_brushsides = lumps[9].length / sizeof(BSP_BRUSHSIDE);

	bsp->vertices = (BSP_VERTEX*)(data + lumps[10].offset);
	bsp->n_vertices = lumps[10].length / sizeof(BSP_VERTEX);

	bsp->meshverts = (BSP_MESHVERT*)(data + lumps[11].offset);
	bsp->n_meshverts = lumps[11].length / sizeof(BSP_MESHVERT);

	bsp->effects = (BSP_EFFECT*)(data + lumps[12].offset);
	bsp->n_effects = lumps[12].length / sizeof(BSP_EFFECT);

	bsp->faces = (BSP_FACE*)(data + lumps[13].offset);
	bsp->n_faces = lumps[13].length / sizeof(BSP_FACE);

	bsp->lightmaps = (BSP_LIGHTMAP*)(data + lumps[14].offset);
	bsp->n_lightmaps = lumps[14].length / sizeof(BSP_LIGHTMAP);

	bsp->lightvolumes = (BSP_LIGHTVOLUME*)(data + lumps[15].offset);
	bsp->n_lightvolumes = lumps[15].length / sizeof(BSP_LIGHTVOLUME);

	bsp->visdata = (BSP_VISDATA*)(data + lumps[16].offset);
	bsp->visdata->vecs = (char*)(bsp->visdata + sizeof(int) * 2);

	return bsp;
}

void freebsp(BSP_DATA* bsp)
{
	free(bsp);
}