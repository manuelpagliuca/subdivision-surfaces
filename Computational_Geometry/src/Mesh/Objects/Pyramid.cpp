#include "Pyramid.h"

Pyramid::Pyramid()
{
	const GLfloat pyramidVertices[] = {
		-.5f,  -.5f,  .0f,
		.5f,  -.5f,  .0f,
		.0f,   1.f, .5f,
		.0f,  -.5f,  1.25f
	};

	const unsigned pyramidIndices[] = {
		0, 2, 1,
		2, 1, 3,
		1, 3, 0,
		0, 3, 2
	};

	createMesh(pyramidVertices, pyramidIndices, 12, 12);
}