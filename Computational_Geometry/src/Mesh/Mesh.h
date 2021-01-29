#pragma once

#include <GL/glew.h>
#include "../Utility/Utility.h"
#include "../GUI/GUI.h"
#include <vector>

class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	/* member function */
	void createMesh(const GLfloat* m_vertices, const unsigned int* m_indices, const unsigned numOfVertices, const unsigned numOfIndices);
	void renderMesh(const bool wireframe_mode);
	void renderPatch(const unsigned patchVertices, const bool wireframe_mode);

	void clearMesh();

	/* getters/setters */
	const int getVertexCount() const;
	const int getIndexCount() const;

	/* generic */
	void setVertexCount(const int t_vertexCount);
	void setIndexCount(const int t_indexCount);

protected:
	GLuint VAO{};
	GLuint VBO{};
	GLuint IBO{};

	GLsizei m_indexCount{};
	GLsizei m_vertexCount{};
};