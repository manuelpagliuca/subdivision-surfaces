#include <iostream>
#include <iomanip>
#include <cmath>

#include "GL/glew.h"
#include "Prism.h"

Prism::Prism(const float baseRadius, const float topRadius, const float height, const int sectors, const int stacks)
{
	set(baseRadius, topRadius, height, sectors, stacks);
}

/* function that build the entire shape using args */
void Prism::set(const float baseRadius, const float topRadius, const float height, const int sectors, const int stacks)
{
	this->baseRadius = baseRadius;
	this->topRadius = topRadius;
	this->height = height;

	this->sectorCount = sectors;
	if (sectors < MIN_SECTOR_COUNT)
		this->sectorCount = MIN_SECTOR_COUNT;

	this->stackCount = stacks;
	if (stacks < MIN_STACK_COUNT)
		this->stackCount = MIN_STACK_COUNT;

	buildUnitCircleVertices();
	buildVerticesFlat();
}

/* Function that generates vertices and indices of the Prism */
void Prism::buildVerticesFlat()
{
	// tmp vertex definition (x,y,z)
	struct Vertex
	{
		float x, y, z;
	};
	std::vector<Vertex> tmpVertices;

	int i, j, k;    // indices
	float x, y, z, radius;

	// put tmp vertices of cylinder side to array by scaling unit circle
	//NOTE: start and end vertex positions are same, but texcoords are different
	//      so, add additional vertex at the end point
	for (i = 0; i <= stackCount; ++i)
	{
		z = -(height * .5f) + static_cast<float>(i) / static_cast<float>(stackCount) * height;      // vertex position z
		radius = baseRadius + static_cast<float>(i) / static_cast<float>(stackCount) * (topRadius - baseRadius); // lerp

		for (j = 0, k = 0; j <= sectorCount; ++j, k += 3)
		{
			x = unitCircleVertices[k];
			y = unitCircleVertices[k + 1];

			Vertex vertex;
			vertex.x = x * radius;
			vertex.y = y * radius;
			vertex.z = z;

			tmpVertices.push_back(vertex);
		}
	}

	// clear memory of prev arrays
	clearArrays();

	Vertex v1, v2, v3, v4;      // 4 vertex positions v1, v2, v3, v4
	int vi1, vi2;               // indices
	int index = 0;

	// v2-v4 <== stack at i+1
	// | \ |
	// v1-v3 <== stack at i
	for (i = 0; i < stackCount; ++i)			//	start from the lowest stack
	{
		vi1 = i * (sectorCount + 1);            // index of tmpVertices
		vi2 = (i + 1) * (sectorCount + 1);

		for (j = 0; j < sectorCount; ++j, ++vi1, ++vi2)	// lap around the sector vertices and construct the indices
		{
			v1 = tmpVertices[vi1];
			v2 = tmpVertices[vi2];
			v3 = tmpVertices[vi1 + 1];
			v4 = tmpVertices[vi2 + 1];

			// put quad vertices: v1-v2-v3-v4
			addVertex(v1.x, v1.y, v1.z);
			addVertex(v2.x, v2.y, v2.z);
			addVertex(v3.x, v3.y, v3.z);
			addVertex(v4.x, v4.y, v4.z);

			// put indices of a quad
			addIndices(index, index + 2, index + 1);    // v1-v3-v2
			addIndices(index + 1, index + 2, index + 3);// v2-v3-v4

			index += 4;     // for next
		}
	}

	// remember where the base index starts
	const unsigned baseVertexIndex = static_cast<unsigned>(vertices.size()) / 3; // number of vertices (latest vertex index)

	// put vertices of base of cylinder
	z = -height * 0.5f;
	addVertex(0, 0, z);
	for (i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		addVertex(x * baseRadius, y * baseRadius, z);
	}

	// put indices for base
	for (i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < sectorCount - 1) // indices from the second vertex to the last
			addIndices(baseVertexIndex, k + 1, k);
		else //	latest loop -> put the first index
			addIndices(baseVertexIndex, baseVertexIndex + 1, k);
	}

	// remember where the top index starts
	const unsigned topVertexIndex = static_cast<unsigned>(vertices.size()) / 3;

	// put vertices of top of cylinder
	z = height * 0.5f;
	addVertex(0, 0, z);

	for (i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		addVertex(x * topRadius, y * topRadius, z);
	}

	for (i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < sectorCount - 1)
			addIndices(topVertexIndex, k, k + 1);
		else
			addIndices(topVertexIndex, k, topVertexIndex + 1);
	}
}

/* Aux function that genarates the vertices of the unit circle */
void Prism::buildUnitCircleVertices()
{
	const float PI = acosf(-1.f);
	const float equation = 2.f * PI / static_cast<float>(sectorCount);
	float sectorAngle;

	std::vector<float>().swap(unitCircleVertices);
	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * equation;
		unitCircleVertices.push_back(cosf(sectorAngle)); // x
		unitCircleVertices.push_back(sinf(sectorAngle)); // y
		unitCircleVertices.push_back(0.f);               // z
	}
}

/* aux function for add vertices inside the vector for opengl data */
void Prism::addVertex(const float x, const float y, const float z)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

/* aux function for add indices inside the vector for opengl data */
void Prism::addIndices(const unsigned i1, const unsigned i2, const unsigned i3)
{
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}

/* aux function for cleaning the opengl vertices and indices data */
void Prism::clearArrays()
{
	std::vector<float>().swap(vertices);
	std::vector<unsigned>().swap(indices);
}


/* getters and setters */
const float Prism::getBaseRadius() const
{
	return baseRadius;
}

const float Prism::getTopRadius() const
{
	return topRadius;
}

const float Prism::getHeight() const
{
	return height;
}

const int Prism::getSectorCount() const
{
	return sectorCount;
}

const int Prism::getStackCount() const
{
	return stackCount;
}

void Prism::setBaseRadius(const float radius)
{
	if (this->baseRadius != radius)
		set(radius, topRadius, height, sectorCount, stackCount);
}

void Prism::setTopRadius(const float radius)
{
	if (this->topRadius != radius)
		set(baseRadius, radius, height, sectorCount, stackCount);
}

void Prism::setHeight(const float height)
{
	if (this->height != height)
		set(baseRadius, topRadius, height, sectorCount, stackCount);
}

void Prism::setSectorCount(const int sectors)
{
	if (this->sectorCount != sectors)
		set(baseRadius, topRadius, height, sectors, stackCount);
}

void Prism::setStackCount(const int stacks)
{
	if (this->stackCount != stacks)
		set(baseRadius, topRadius, height, sectorCount, stacks);
}

const unsigned int Prism::getVertexCount() const
{
	return static_cast<unsigned>(vertices.size());
}

const unsigned int Prism::getIndexCount() const
{
	return static_cast<unsigned>(indices.size());
}

const unsigned int Prism::getTriangleCount() const
{
	return getIndexCount() / 3;
}

const unsigned int Prism::getVertexSize() const
{
	return static_cast<unsigned>(vertices.size()) * sizeof(float);
}

const unsigned int Prism::getIndexSize() const
{
	return static_cast<unsigned>(indices.size()) * sizeof(unsigned);
}

const float* Prism::getVertices() const
{
	return vertices.data();
}

const unsigned int* Prism::getIndices() const
{
	return indices.data();
}

// for indices of base/top/side parts
const unsigned int Prism::getBaseIndexCount() const
{
	return static_cast<unsigned>(indices.size()) - baseIndex / 2;
}

const unsigned int Prism::getTopIndexCount() const
{
	return static_cast<unsigned>(indices.size()) - baseIndex / 2;
}

const unsigned int Prism::getSideIndexCount() const
{
	return baseIndex;
}

const unsigned int Prism::getBaseStartIndex() const
{
	return baseIndex;
}

const unsigned int Prism::getTopStartIndex() const
{
	return topIndex;
}

const unsigned int Prism::getSideStartIndex() const
{
	return 0;
}

/* debug */

void Prism::printSelf() const
{
	std::cout << "===== Cylinder =====\n"
		<< "   Base Radius: " << baseRadius << "\n"
		<< "    Top Radius: " << topRadius << "\n"
		<< "        Height: " << height << "\n"
		<< "  Sector Count: " << sectorCount << "\n"
		<< "   Stack Count: " << stackCount << "\n"
		<< "Triangle Count: " << getTriangleCount() << "\n"
		<< "   Index Count: " << getIndexCount() << "\n"
		<< "  Vertex Count: " << getVertexCount() << "\n";
}