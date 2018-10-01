#include "bsprenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bsp.h"

BSP_RENDEROBJECT* setupBsp(BSP_DATA* bsp)
{
	BSP_RENDEROBJECT* renderobject = (BSP_RENDEROBJECT*)malloc(sizeof(BSP_RENDEROBJECT));

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BSP_VERTEX) * bsp->n_vertices, bsp->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(BSP_MESHVERT) * bsp->n_meshverts, bsp->meshverts, GL_STATIC_DRAW);

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

	renderobject->data = bsp;
	renderobject->EBO = EBO;
	renderobject->VAO = VAO;
	renderobject->VBO = VBO;

	renderobject->renderqueue = (BSP_FACE**)malloc(sizeof(BSP_FACE*) * bsp->n_faces);

	return renderobject;
}

void fillRenderQueue(BSP_FACE** renderqueue, BSP_DATA* bsp, unsigned int* length)
{
	*length = bsp->models[0].n_faces;

	for (int i = 0; i < *length; i++)
	{
		renderqueue[i] = (BSP_FACE*)(bsp->faces + bsp->models[0].face + i);
	}
	
	return renderqueue;
}

void renderBsp(BSP_RENDEROBJECT* renderobject)
{
	glBindVertexArray(renderobject->VAO);

	int length;

	fillRenderQueue(renderobject->renderqueue, renderobject->data, &length);

	for (int i = 0; i < length; i++)
	{
		BSP_FACE* face = renderobject->renderqueue[i];

		glDrawElementsBaseVertex(GL_TRIANGLES, face->n_meshverts, GL_UNSIGNED_INT, face->meshvert*sizeof(int), face->vertex);
	}

	glBindVertexArray(0);
}