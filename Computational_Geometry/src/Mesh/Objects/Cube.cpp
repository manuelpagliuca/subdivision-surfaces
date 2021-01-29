#include "Cube.h"

Cube::Cube(CubeMeshType meshType)
{
	GLfloat cubeVertices[] = {
		-0.50f, -0.50f, -0.50f,
		-0.50f,  0.50f, -0.50f,
		 0.50f, -0.50f, -0.50f,
		 0.50f,  0.50f, -0.50f,
		 0.50f, -0.50f,  0.50f,
		 0.50f,  0.50f,  0.50f,
		-0.50f, -0.50f,  0.50f,
		-0.50f,  0.50f,  0.50f,
	};

	if (meshType == CubeMeshType::TriangularMesh) {
		unsigned cubeIndicesTrian[] =
		{
			0,1,2,
			2,1,3,
			3,5,2,
			2,4,5,
			5,6,4,
			6,7,5,
			7,6,0,
			0,7,1,
			7,5,1,
			1,5,3,
			6,4,0,
			4,0,2
		};

		createMesh(cubeVertices, cubeIndicesTrian, 24, 36);
	}
	else if (meshType == CubeMeshType::QuadrilateralMesh) {
		GLuint cubeIndicesQuad[] =
		{
			0, 1, 2, 3,
			2, 3, 4, 5,
			4, 5, 6, 7,
			6, 7, 0, 1,
			0, 2, 6, 4,
			1, 7, 3, 5
		};

		createMesh(cubeVertices, cubeIndicesQuad, 24, 24);
	}
}

void Cube::renderPatch(const bool wireframe_mode)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode ? GL_LINE : GL_FILL);
	glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Cube::~Cube()
{
}