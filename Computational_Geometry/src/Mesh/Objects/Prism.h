#pragma once

#include <vector>
#include "../Mesh.h"

class Prism : public Mesh
{
public:
	Prism(const float baseRadius = 1.f, const float topRadius = 1.f, const float height = 1.f, const int sectorCount = 3, const int stackCount = 1);
	~Prism() {}

	/* main function */
	void set(const float baseRadius, const float topRadius, const float height, const int sectorCount, const int stackCount);

	/* getters and setters */
	const float getBaseRadius() const;
	const float getTopRadius() const;
	const float getHeight() const;
	const int getSectorCount() const;
	const int getStackCount() const;
	const unsigned int getVertexCount() const;
	const unsigned int getIndexCount() const;
	const unsigned int getTriangleCount() const;
	const unsigned int getVertexSize() const;
	const unsigned int getIndexSize() const;
	const unsigned int getBaseIndexCount() const;
	const unsigned int getTopIndexCount() const;
	const unsigned int getSideIndexCount() const;
	const unsigned int getBaseStartIndex() const;
	const unsigned int getTopStartIndex() const;
	const unsigned int getSideStartIndex() const;
	const float* getVertices() const;
	const unsigned int* getIndices() const;
	void setBaseRadius(const float radius);
	void setTopRadius(const float radius);
	void setHeight(const float radius);
	void setSectorCount(const int sectorCount);
	void setStackCount(const int stackCount);

	// debug
	void printSelf() const;

private:
	// Build unit circle
	void buildUnitCircleVertices();

	// Build vertices and indices
	void buildVerticesFlat();

	// Prism Data 
	float baseRadius;
	float topRadius;
	float height;
	int sectorCount;
	int stackCount;
	unsigned baseIndex;
	unsigned topIndex;
	std::vector<float> unitCircleVertices;

	// OpenGL Data
	std::vector<float> vertices;
	std::vector<unsigned> indices;

	// Aux functions
	void clearArrays();
	void addVertex(const float x, const float y, const float z);
	void addIndices(const unsigned i1, const unsigned i2, const unsigned i3);

private:
	const int MIN_SECTOR_COUNT = 3;
	const int MIN_STACK_COUNT = 1;
};