#pragma once

#include "../Mesh.h"

enum class CubeMeshType {
	TriangularMesh,
	QuadrilateralMesh
};

struct Cube : public Mesh
{
	Cube() = default;
	Cube(CubeMeshType meshType);
	~Cube();
	virtual void renderPatch(const bool wireframe_mode);
};