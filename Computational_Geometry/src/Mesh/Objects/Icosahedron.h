#pragma once

#include <vector>
#include <map>

#include "../Mesh.h"

class Icosahedron : public Mesh
{
public:
	Icosahedron(const float t_radius, const int t_subdivision = 0, const float t_radV1 = 1.f, const float t_radV2 = 1.f, const float t_radV3 = 1.f);
	~Icosahedron() {}

	/* getters and setters */
	const float getRadius() const;
	const int getSubdivision() const;
	const unsigned int getVertexCount() const;
	const unsigned int getVertexSize() const;
	const float* getVertices() const;
	const unsigned int getIndexCount() const;
	const unsigned int getIndexSize() const;
	const unsigned int* getIndices() const;
	const MiddlepointsRadius getMiddlepoints() const;

	void setRadius(const float t_radius);
	void setSubdivision(const int t_subdivision);
	void setSubdividedVerticesRadiuses(const float t_mid1, const float t_mid2, const float t_mid3);
	void setMiddlepoints(const float t_midpointrad1, const float t_midpointrad2, const float t_midpointrad3);

	// debug
	void printSelf() const;

private:
	inline void updateRadius();

	std::vector<float> computeIcosahedronVertices();
	void buildVerticesFlat();
	void subdivideVerticesFlat();

	void addVertex(const float x, const float y, const float z)
	{
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(z);
	}

	void addVertices(const float v1[3], const float v2[3], const float v3[3]);

	void addIndices(const unsigned i1, const unsigned i2, const unsigned i3)
	{
		m_indices.push_back(i1);
		m_indices.push_back(i2);
		m_indices.push_back(i3);
	}

	static inline void computeHalfVertex(const float v1[3], const float v2[3], const float length, float newV[3]);
	static const float computeScaleForLength(const float v[3], const float length)
	{
		return length / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}

	/* members */
	float m_radius{};
	MiddlepointsRadius m_middlePoints{};

	float m_radiusMidpoint1{ 1.0f };
	float m_radiusMidpoint2{ 1.0f };
	float m_radiusMidpoint3{ 1.0f };

	int m_subdivision{};

	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
};