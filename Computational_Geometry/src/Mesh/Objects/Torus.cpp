#include "Torus.h"

/* Function that generates the vertices of the torus */
void Torus::buildVertices()
{
	std::vector<float>().swap(m_vertices);

	const float mainSegmentAngleStep = glm::radians(360.0f / float(m_mainSegments));
	const float tubeSegmentAngleStep = glm::radians(360.0f / float(m_tubeSegments));

	float currentMainSegmentAngle = 0.0f;

	for (int i = 0; i <= m_mainSegments; i++)
	{
		// Calculate sine and cosine of main segment angle
		const float sinMainSegment = sinf(currentMainSegmentAngle);
		const float cosMainSegment = cosf(currentMainSegmentAngle);
		float currentTubeSegmentAngle = 0.f;

		for (int j = 0; j <= m_tubeSegments; j++)
		{
			// Calculate sine and cosine of tube segment angle
			const float sinTubeSegment = sinf(currentTubeSegmentAngle);
			const float cosTubeSegment = cosf(currentTubeSegmentAngle);

			// Calculate vertex position on the surface of torus
			const float x = (m_mainRadius + m_tubeRadius * cosTubeSegment) * cosMainSegment;
			const float y = (m_mainRadius + m_tubeRadius * cosTubeSegment) * sinMainSegment;
			const float z = (m_tubeRadius * sinTubeSegment);

			m_vertices.push_back(x);
			m_vertices.push_back(y);
			m_vertices.push_back(z);

			// Update current tube angle
			currentTubeSegmentAngle += tubeSegmentAngleStep;
		}

		// Update main segment angle
		currentMainSegmentAngle += mainSegmentAngleStep;
	}
}

/* Function that generates the indices of the torus */
void Torus::buildIndices()
{
	std::vector<unsigned int>().swap(m_indices);

	unsigned index = 0;

	for (int i = 0; i < m_mainSegments; ++i)
	{
		for (int j = 0; j <= m_tubeSegments; ++j)
		{
			m_indices.push_back(index);
			m_indices.push_back(index + 1);
			m_indices.push_back(index + m_tubeSegments);

			m_indices.push_back(index + 1);
			m_indices.push_back(index + m_tubeSegments + 1);
			m_indices.push_back(index + m_tubeSegments);
			index++;
		}
	}
}

/* getters and setters */

void Torus::setMainRadius(const float t_radius)
{
	m_mainRadius = t_radius;
}

void Torus::setTubeRadius(const float t_radius)
{
	m_tubeRadius = t_radius;
}

void Torus::setMainSegments(const int t_mainSegments)
{
	m_mainSegments = t_mainSegments;
}

void Torus::setTubeSegments(const int t_tubeSegments)
{
	m_tubeSegments = t_tubeSegments;
}

float Torus::getMainRadius() const
{
	return m_mainRadius;
}

float Torus::getTubeRadius() const
{
	return m_tubeRadius;
}

const int Torus::getMainSegments() const
{
	return m_mainSegments;
}

const int Torus::getTubeSegments() const
{
	return m_tubeSegments;
}

const float* Torus::getVertices() const
{
	return m_vertices.data();
}

const unsigned int Torus::getVerticesCount() const
{
	return m_vertices.size();
}

const unsigned int* Torus::getIndices() const
{
	return m_indices.data();
}

const unsigned int Torus::getIndicesCount() const
{
	return m_indices.size();
}