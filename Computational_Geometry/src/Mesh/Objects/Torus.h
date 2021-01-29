#pragma once

#include "../Mesh.h"

class Torus : public Mesh
{
public:
	Torus(const int t_mainSegments, const int t_tubeSegments, const float t_mainRadius, const float t_tubeRadius) :
		m_mainSegments{ t_mainSegments }, m_tubeSegments{ t_tubeSegments }, m_mainRadius{ t_mainRadius }, m_tubeRadius{ t_tubeRadius }
	{
		buildVertices();
		buildIndices();
	}

	/* getters and setters */
	void setMainRadius(const float t_radius);
	void setTubeRadius(const float t_radius);
	void setMainSegments(const int t_mainSegments);
	void setTubeSegments(const int t_tubeSegments);
	float getMainRadius() const;
	float getTubeRadius() const;
	const int getMainSegments() const;
	const int getTubeSegments() const;
	const float* getVertices() const;
	const unsigned int getVerticesCount() const;
	const unsigned int* getIndices() const;
	const unsigned int getIndicesCount() const;

private:
	// torus data
	int m_mainSegments{};
	int m_tubeSegments{};
	float m_mainRadius{};
	float m_tubeRadius{};

	// opengl data
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	// building functions
	void buildVertices();
	void buildIndices();
};