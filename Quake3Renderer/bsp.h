#ifndef BSP_H
#define BSP_H

typedef struct {
	char name[64];
	int flags;
	int contents;
} BSP_TEXTURE;

typedef struct {
	float normal[3];
	float distance;
} BSP_PLANE;

typedef struct {
	int plane;
	int children[2];
	int min[3];
	int max[3];
} BSP_NODE;

typedef struct {
	int cluster;
	int area;
	int min[3];
	int max[3];
	int leafface;
	int n_leaffaces;
	int leafbrush;
	int n_leafbrushes;
} BSP_LEAF;

typedef struct {
	int face;
} BSP_LEAFFACE;

typedef struct {
	int brush;
} BSP_LEAFBRUSH;

typedef struct {
	float min[3];
	float max[3];
	int face;
	int n_faces;
	int brush;
	int n_brushes;
} BSP_MODEL;

typedef struct {
	int brushside;
	int n_brushsides;
	int texture;
} BSP_BRUSH;

typedef struct {
	int plane;
	int texture;
} BSP_BRUSHSIDE;

typedef struct {
	float position[3];
	float texcoord[2][2];
	float normal[3];
	unsigned char color[4];
} BSP_VERTEX;

typedef struct {
	int offset;
} BSP_MESHVERT;

typedef struct {
	char* name;
	int brush;
	int unknown;
} BSP_EFFECT;

typedef struct {
	int texture;
	int effect;
	int type;
	int vertex;
	int n_vertices;
	int meshvert;
	int n_meshverts;
	int lm_index;
	int lm_start[2];
	int lm_size[2];
	float lm_origin[3];
	float lm_vecs[2][3];
	float normal[3];
	int size[2];
} BSP_FACE;

typedef struct {
	char* data;
} BSP_LIGHTMAP;

typedef struct {
	unsigned char ambient[3];
	unsigned char directional[3];
	unsigned char dir[2];
} BSP_LIGHTVOLUME;

typedef struct {
	int n_vecs;
	int sz_vecs;
	unsigned char* vecs;
} BSP_VISDATA;

typedef struct {
	char* entities;
	BSP_TEXTURE* textures;
	int n_textures;
	BSP_PLANE* planes;
	int n_planes;
	BSP_NODE* nodes;
	int n_nodes;
	BSP_LEAF* leaves;
	int n_leaves;
	BSP_LEAFFACE* leaffaces;
	int n_leaffaces;
	BSP_LEAFBRUSH* leafbrushes;
	int n_leafbrushes;
	BSP_MODEL* models;
	int n_models;
	BSP_BRUSH* brushes;
	int n_brushes;
	BSP_BRUSHSIDE* brushsides;
	int n_brushsides;
	BSP_VERTEX* vertices;
	int n_vertices;
	BSP_MESHVERT* meshverts;
	int n_meshverts;
	BSP_EFFECT* effects;
	int n_effects;
	BSP_FACE* faces;
	int n_faces;
	BSP_LIGHTMAP* lightmaps;
	int n_lightmaps;
	BSP_LIGHTVOLUME* lightvolumes;
	int n_lightvolumes;
	BSP_VISDATA* visdata;
} BSP_DATA;

BSP_DATA* loadbsp(char* data);
void freebsp(BSP_DATA* bsp);

#endif 