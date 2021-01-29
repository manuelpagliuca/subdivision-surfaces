#include "Mesh.h"

/* member functions */
void Mesh::createMesh(const GLfloat* m_vertices, const unsigned int* m_indices, const unsigned numOfVertices, const unsigned numOfIndices)
{
	m_indexCount = numOfIndices;
	m_vertexCount = numOfVertices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * numOfVertices, m_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * numOfIndices, m_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::renderMesh(const bool wireframe_mode)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode ? GL_LINE : GL_FILL);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderPatch(const unsigned patchVertices, const bool wireframe_mode)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glPatchParameteri(GL_PATCH_VERTICES, patchVertices);
	glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode ? GL_LINE : GL_FILL);
	glDrawElements(GL_PATCHES, m_indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/* getters */
const int Mesh::getVertexCount() const
{
	return m_vertexCount;
}

const int Mesh::getIndexCount() const
{
	return m_indexCount;
}

/* setters */
void Mesh::setVertexCount(const int t_vertexCount)
{
	m_vertexCount = t_vertexCount;
}

void Mesh::setIndexCount(const int t_indexCount)
{
	m_indexCount = t_indexCount;
}

/* dtor functions */
void Mesh::clearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	m_indexCount = 0;
}

Mesh::~Mesh()
{
	clearMesh();
}