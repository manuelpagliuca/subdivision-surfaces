#include <iostream>

#include "Icosahedron.h"

/* ctor */
Icosahedron::Icosahedron(const float t_radius, const int t_subdivision, const float t_radV1, const float t_radV2, const float t_radV3)
	: m_radius(t_radius), m_subdivision(t_subdivision), m_radiusMidpoint1(t_radV1), m_radiusMidpoint2(t_radV2), m_radiusMidpoint3(t_radV3)
{
	buildVerticesFlat();
}

void Icosahedron::updateRadius()
{
	const float scale = computeScaleForLength(&m_vertices[0], m_radius);

	std::size_t i, j;
	std::size_t count = m_vertices.size();
	for (i = 0, j = 0; i < count; i += 3, j += 8)
	{
		m_vertices[i] *= scale;
		m_vertices[i + 1] *= scale;
		m_vertices[i + 2] *= scale;
	}
}

std::vector<float> Icosahedron::computeIcosahedronVertices()
{
	float const PI = acosf(-1.f);
	float const H_ANGLE = PI / 180.f * 72.f;    // horizontal rotation di 72°
	float const V_ANGLE = atanf(1.0f / 2.f);    // vertical rotation (elevation) of 26.565°

	float hAngle1 = -PI / 2.f - H_ANGLE / 2.f;  // 1st row starts at -126°
	float hAngle2 = -PI / 2.f;                  // 2nd row starts at -90°

	float const z = m_radius * sinf(V_ANGLE);
	float const xy = m_radius * cosf(V_ANGLE);

	std::vector<float> icoVertices(12 * 3);     // 12 m_vertices

	// first vertex (0, 0, r)
	icoVertices[0] = 0.f;
	icoVertices[1] = 0.f;
	icoVertices[2] = m_radius;

	int i1, i2;

	for (int i = 1; i <= 5; ++i)
	{
		i1 = i * 3;       // 1st row
		i2 = (i + 5) * 3; // 2nd row

		icoVertices[i1] = xy * cosf(hAngle1);
		icoVertices[i1 + 1L] = xy * sinf(hAngle1);
		icoVertices[i1 + 2L] = z;

		icoVertices[i2] = xy * cosf(hAngle2);
		icoVertices[i2 + 1L] = xy * sinf(hAngle2);
		icoVertices[i2 + 2L] = -z;

		// next horizontal angles
		hAngle1 += H_ANGLE;
		hAngle2 += H_ANGLE;
	}

	// last vertex (0, 0, -r)
	i1 = 11 * 3;
	icoVertices[i1] = 0;
	icoVertices[i1 + 1L] = 0;
	icoVertices[i1 + 2L] = -m_radius;

	return icoVertices;
}

void Icosahedron::buildVerticesFlat()
{
	std::vector<float> tmpVertices = computeIcosahedronVertices();
	std::vector<float>().swap(m_vertices);
	std::vector<unsigned int>().swap(m_indices);

	float const* v0 = &tmpVertices[0];       // 1st vertex
	float const* v11 = &tmpVertices[11 * 3]; // 12th vertex
	float const* v1, * v2, * v3, * v4;		 // 2nd row m_vertices

	unsigned index = 0;

	for (int i = 1; i <= 5; ++i)
	{
		// 4 m_vertices in the 2nd row
		v1 = &tmpVertices[static_cast<long long>(i) * 3L];

		if (i < 5)
			v2 = &tmpVertices[(static_cast<long long>(i) + 1L) * 3L];
		else
			v2 = &tmpVertices[3];

		v3 = &tmpVertices[(static_cast<long long>(i) + 5L) * 3L];
		if ((i + 5) < 10)
			v4 = &tmpVertices[(static_cast<long long>(i) + 6L) * 3L];
		else
			v4 = &tmpVertices[6 * 3];

		// add a triangle in 1st row
		addVertices(v0, v1, v2);
		addIndices(index, index + 1, index + 2);

		// add 2 triangles in 2nd row
		addVertices(v1, v3, v2);
		addIndices(index + 3, index + 4, index + 5);

		addVertices(v2, v3, v4);
		addIndices(index + 6, index + 7, index + 8);

		// add a triangle in 3rd row
		addVertices(v3, v11, v4);
		addIndices(index + 9, index + 10, index + 11);

		// next index
		index += 12;
	}

	// subdivide icosahedron
	subdivideVerticesFlat();
}

void Icosahedron::subdivideVerticesFlat()
{
	std::vector<float> tmpVertices;
	std::vector<unsigned int> tmpIndices;
	const float* v1, * v2, * v3;			// ptr to original m_vertices of a triangle
	float newV1[3], newV2[3], newV3[3];		// new vertex positions
	unsigned index = 0;						// new index value
	int i, j;

	// iteration
	for (i = 1; i <= m_subdivision; ++i)
	{
		// copy prev arrays
		tmpVertices = m_vertices;
		tmpIndices = m_indices;

		// clear prev arrays
		m_vertices.clear();
		m_indices.clear();

		index = 0;
		int const m_indexCount = static_cast<int const>(tmpIndices.size());

		for (j = 0; j < m_indexCount; j += 3)
		{
			// avoiding arithmetic overflow
			unsigned const j_2 = j + 1;
			unsigned const j_3 = j + 2;

			v1 = &tmpVertices[static_cast<long long>(tmpIndices[j]) * 3L];
			v2 = &tmpVertices[static_cast<long long>(tmpIndices[j_2]) * 3L];
			v3 = &tmpVertices[static_cast<long long>(tmpIndices[j_3]) * 3L];

			// compute 3 new m_vertices by spliting half on each edge
			//         v1
			//        / \
			// newV1 *---* newV3
			//      / \ / \
			//    v2---*---v3
			//       newV2

			// get 3 new m_vertices by spliting half on each edge
			computeHalfVertex(v1, v2, m_radiusMidpoint1, newV1);
			computeHalfVertex(v2, v3, m_radiusMidpoint2, newV2);
			computeHalfVertex(v1, v3, m_radiusMidpoint3, newV3);

			// add 4 new triangles
			addVertices(v1, newV1, newV3);
			addIndices(index, index + 1, index + 2);

			addVertices(newV1, v2, newV2);
			addIndices(index + 3, index + 4, index + 5);

			addVertices(newV1, newV2, newV3);
			addIndices(index + 6, index + 7, index + 8);

			addVertices(newV3, newV2, v3);
			addIndices(index + 9, index + 10, index + 11);

			// next index
			index += 12;
		}
	}
}

void Icosahedron::addVertices(const float v1[3], const float v2[3], const float v3[3])
{
	/* v1 */
	m_vertices.push_back(v1[0]);
	m_vertices.push_back(v1[1]);
	m_vertices.push_back(v1[2]);
	/* v2 */
	m_vertices.push_back(v2[0]);
	m_vertices.push_back(v2[1]);
	m_vertices.push_back(v2[2]);
	/* v3 */
	m_vertices.push_back(v3[0]);
	m_vertices.push_back(v3[1]);
	m_vertices.push_back(v3[2]);
}

void Icosahedron::computeHalfVertex(const float v1[3], const float v2[3], const float length, float newV[3])
{
	/* find the vector passing through the middle point */
	newV[0] = v1[0] + v2[0];
	newV[1] = v1[1] + v2[1];
	newV[2] = v1[2] + v2[2];

	/* calculate the scaling factor using the radius */
	const float scale = Icosahedron::computeScaleForLength(newV, length);

	/* apply the scaling factor*/
	newV[0] *= scale;
	newV[1] *= scale;
	newV[2] *= scale;
}

/* getters and setters */

const float Icosahedron::getRadius() const
{
	return m_radius;
}

const int Icosahedron::getSubdivision() const
{
	return m_subdivision;
}

const unsigned int Icosahedron::getVertexCount() const
{
	return static_cast<const unsigned int>(m_vertices.size());
}

const unsigned int Icosahedron::getVertexSize() const
{
	return static_cast<const unsigned int>(m_vertices.size() * sizeof(float));
}

const float* Icosahedron::getVertices() const
{
	return m_vertices.data();
}

const unsigned int Icosahedron::getIndexCount() const
{
	return static_cast<const unsigned int>(m_indices.size());
}

const unsigned int Icosahedron::getIndexSize() const
{
	return static_cast<const unsigned int>(m_indices.size() * sizeof(unsigned int));
}

const unsigned int* Icosahedron::getIndices() const
{
	return m_indices.data();
}

const MiddlepointsRadius Icosahedron::getMiddlepoints() const
{
	return m_middlePoints;
}

void Icosahedron::setRadius(const float t_radius)
{
	this->m_radius = t_radius;
	updateRadius();
}

void Icosahedron::setSubdivision(const int t_subdivision)
{
	this->m_subdivision = t_subdivision;
	buildVerticesFlat();
}

void Icosahedron::setSubdividedVerticesRadiuses(const float t_mid1, const float t_mid2, const float t_mid3)
{
	m_radiusMidpoint1 = t_mid1;
	m_radiusMidpoint2 = t_mid2;
	m_radiusMidpoint3 = t_mid3;
	buildVerticesFlat();
}

void Icosahedron::setMiddlepoints(const float t_midpointrad1, const float t_midpointrad2, const float t_midpointrad3)
{
	m_middlePoints.v1 = t_midpointrad1;
	m_middlePoints.v2 = t_midpointrad2;
	m_middlePoints.v3 = t_midpointrad3;
}

/* debug */
void Icosahedron::printSelf() const
{
	std::cout << "===== Icosahedron =====\n"
		<< "        Radius: " << m_radius << "\n"
		<< "   Subdivision: " << m_subdivision << "\n"
		<< "   Index Count: " << getIndexCount() << "\n"
		<< "  Vertex Count: " << getVertexCount() << "\n";
}