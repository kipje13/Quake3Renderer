#include "bsprenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bsp.h"

#include <stdlib.h>

BspRenderer::BspRenderer(BSP_DATA* bsp)
{
	data = bsp;
}

void BspRenderer::setupBsp()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BSP_VERTEX) * data->n_vertices, data->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(BSP_MESHVERT) * data->n_meshverts, data->meshverts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BSP_VERTEX), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BSP_VERTEX), (void*)12);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BSP_VERTEX), (void*)20);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(BSP_VERTEX), (void*)28);
	glVertexAttribPointer(4, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(BSP_VERTEX), (void*)40);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	renderqueue = (BSP_FACE**)malloc(sizeof(BSP_FACE*) * data->n_faces);

	lightmaps = (unsigned int*)malloc(sizeof(unsigned int)*data->n_lightmaps);

	generateLightmaps();
}

void fillRenderQueue(BSP_FACE** renderqueue, BSP_DATA* bsp, int* length)
{
	*length = bsp->models[0].n_faces;

	for (int i = 0; i < *length; i++)
	{
		renderqueue[i] = (BSP_FACE*)(bsp->faces + bsp->models[0].face + i);
	}
}

void BspRenderer::renderBsp()
{
	glBindVertexArray(VAO);

	int length;

	fillRenderQueue(renderqueue, data, &length);

	for (int i = 0; i < length; i++)
	{
		BSP_FACE* face = renderqueue[i];

		if (face->lm_index > -1)
			glBindTexture(GL_TEXTURE_2D, lightmaps[face->lm_index]);

		glDrawElementsBaseVertex(GL_TRIANGLES, face->n_meshverts, GL_UNSIGNED_INT, (void*)(face->meshvert*sizeof(int)), face->vertex);
	}

	glBindVertexArray(0);
}

void BspRenderer::generateLightmaps()
{
	glGenTextures(data->n_lightmaps, lightmaps);

	for (int i = 0; i < data->n_lightmaps; i++)
	{
		glBindTexture(GL_TEXTURE_2D, lightmaps[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, data->lightmaps[i].data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}