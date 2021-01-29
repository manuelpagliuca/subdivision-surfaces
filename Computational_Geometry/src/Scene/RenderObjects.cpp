#include "Scene.h"

/* Handles the changing params of the prism */
void Scene::renderPrism(std::map<int, ObjectGUIParams>& objectParams, const bool wireframeMode, const unsigned guiIndex, const unsigned meshIndex, const int selectedShader)
{
	Prism* oldMesh = static_cast<Prism*>(m_meshes[meshIndex]);

	// Handle sector count
	if (objectParams[guiIndex].prism.sectorCount != oldMesh->getStackCount())
	{
		Prism* cylinder = new Prism(
			oldMesh->getBaseRadius(),
			oldMesh->getTopRadius(),
			oldMesh->getHeight(),
			objectParams[guiIndex].prism.sectorCount,
			oldMesh->getStackCount());

		cylinder->setSectorCount(objectParams[guiIndex].prism.sectorCount);

		cylinder->createMesh(
			cylinder->getVertices(),
			cylinder->getIndices(),
			cylinder->getVertexCount(),
			cylinder->getIndexCount()
		);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = cylinder;
	}
	
	oldMesh = static_cast<Prism*>(m_meshes[meshIndex]);

	if (objectParams[guiIndex].prism.stackCount != oldMesh->getStackCount())
	{
		Prism* cylinder = new Prism(
			oldMesh->getBaseRadius(),
			oldMesh->getTopRadius(),
			oldMesh->getHeight(),
			oldMesh->getSectorCount(),
			objectParams[guiIndex].prism.stackCount);

		cylinder->setStackCount(objectParams[guiIndex].prism.stackCount);

		cylinder->createMesh(
			cylinder->getVertices(),
			cylinder->getIndices(),
			cylinder->getVertexCount(),
			cylinder->getIndexCount()
		);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = cylinder;
	}
	else if (objectParams[guiIndex].prism.baseRadius != oldMesh->getBaseRadius())
	{
		Prism* cylinder = new Prism(
			objectParams[guiIndex].prism.baseRadius,
			oldMesh->getTopRadius(),
			oldMesh->getHeight(),
			oldMesh->getSectorCount(),
			oldMesh->getStackCount());

		cylinder->setBaseRadius(objectParams[guiIndex].prism.baseRadius);

		cylinder->createMesh(
			cylinder->getVertices(),
			cylinder->getIndices(),
			cylinder->getVertexCount(),
			cylinder->getIndexCount()
		);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = cylinder;
	}
	else if (objectParams[guiIndex].prism.topRadius != oldMesh->getTopRadius())
	{
		Prism* cylinder = new Prism(
			oldMesh->getBaseRadius(),
			objectParams[guiIndex].prism.topRadius,
			oldMesh->getHeight(),
			oldMesh->getSectorCount(),
			oldMesh->getStackCount());

		cylinder->setTopRadius(objectParams[guiIndex].prism.topRadius);

		cylinder->createMesh(
			cylinder->getVertices(),
			cylinder->getIndices(),
			cylinder->getVertexCount(),
			cylinder->getIndexCount()
		);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = cylinder;
	}
	else if (objectParams[guiIndex].prism.height != oldMesh->getHeight())
	{
		Prism* cylinder = new Prism(
			oldMesh->getBaseRadius(),
			oldMesh->getTopRadius(),
			objectParams[guiIndex].prism.height,
			oldMesh->getSectorCount(),
			oldMesh->getStackCount());

		cylinder->setHeight(objectParams[guiIndex].prism.height);

		cylinder->createMesh(
			cylinder->getVertices(),
			cylinder->getIndices(),
			cylinder->getVertexCount(),
			cylinder->getIndexCount()
		);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = cylinder;
	}

	if (selectedShader == shader::TRIANG_TESS_SHADER)
		m_meshes[MESH::PRISM]->renderPatch(3, wireframeMode);
	else if (selectedShader == shader::SIMPLE_SHADER)
		m_meshes[MESH::PRISM]->renderMesh(wireframeMode);
}

/* handles the icosahedron changing params */
void Scene::renderIcosahedron(std::map<int, ObjectGUIParams>& objectParams, const bool wireframeMode, const unsigned guiIndex, const unsigned meshIndex, const int selectedShader)
{
	Icosahedron* oldMesh = static_cast<Icosahedron*> (m_meshes[meshIndex]);

	// Handle subdivision level
	if (objectParams[guiIndex].icosahedron.subdivisionLevel != oldMesh->getSubdivision())
	{
		Icosahedron* sphere = new Icosahedron(
			oldMesh->getRadius(),
			objectParams[guiIndex].icosahedron.subdivisionLevel);

		sphere->setSubdividedVerticesRadiuses(
			objectParams[guiIndex].icosahedron.midpointRadius.v1,
			objectParams[guiIndex].icosahedron.midpointRadius.v2,
			objectParams[guiIndex].icosahedron.midpointRadius.v3);

		sphere->setSubdivision(objectParams[guiIndex].icosahedron.subdivisionLevel);

		sphere->createMesh(
			sphere->getVertices(),
			sphere->getIndices(),
			sphere->getVertexCount(),
			sphere->getIndexCount());

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = sphere;
	}
	else if (!approximatelyEqual(objectParams[guiIndex].icosahedron.midpointRadius.v1, oldMesh->getMiddlepoints().v1, 0.0001f) ||
		!approximatelyEqual(objectParams[guiIndex].icosahedron.midpointRadius.v2, oldMesh->getMiddlepoints().v2, 0.0001f) ||
		!approximatelyEqual(objectParams[guiIndex].icosahedron.midpointRadius.v3, oldMesh->getMiddlepoints().v3, 0.0001f))
	{
		Icosahedron* sphere = new Icosahedron(
			objectParams[guiIndex].icosahedron.radius,
			oldMesh->getSubdivision(),
			objectParams[guiIndex].icosahedron.midpointRadius.v1,
			objectParams[guiIndex].icosahedron.midpointRadius.v2,
			objectParams[guiIndex].icosahedron.midpointRadius.v3);

		sphere->setMiddlepoints(
			objectParams[guiIndex].icosahedron.midpointRadius.v1,
			objectParams[guiIndex].icosahedron.midpointRadius.v2,
			objectParams[guiIndex].icosahedron.midpointRadius.v3);

		sphere->createMesh(
			sphere->getVertices(),
			sphere->getIndices(),
			sphere->getVertexCount(),
			sphere->getIndexCount());

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = sphere;
	}
	else if (!approximatelyEqual(objectParams[guiIndex].icosahedron.radius, oldMesh->getRadius(), 0.01f))
	{
		Icosahedron* sphere = new Icosahedron(objectParams[guiIndex].icosahedron.radius, oldMesh->getSubdivision());

		sphere->setSubdividedVerticesRadiuses(
			objectParams[guiIndex].icosahedron.midpointRadius.v1,
			objectParams[guiIndex].icosahedron.midpointRadius.v2,
			objectParams[guiIndex].icosahedron.midpointRadius.v3);

		sphere->setRadius(objectParams[guiIndex].icosahedron.radius);

		sphere->createMesh(
			sphere->getVertices(),
			sphere->getIndices(),
			sphere->getVertexCount(),
			sphere->getIndexCount());

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = sphere;
	}

	if (selectedShader == shader::TRIANG_TESS_SHADER)
		m_meshes[MESH::ICOSAHEDRON]->renderPatch(3, wireframeMode);
	else if (selectedShader == shader::SIMPLE_SHADER)
		m_meshes[MESH::ICOSAHEDRON]->renderMesh(wireframeMode);
}

/* Handles torus params */
void Scene::renderTorus(std::map<int, ObjectGUIParams>& objectParams, const bool wireframeMode, const unsigned guiIndex, const unsigned meshIndex, const int selectedShader)
{
	Torus* oldMesh = static_cast<Torus*>(m_meshes[meshIndex]);

	if (!approximatelyEqual(objectParams[guiIndex].torus.mainRadius, oldMesh->getMainRadius(), 0.01f))
	{
		Torus* torus = new Torus(
			oldMesh->getMainSegments(),
			oldMesh->getTubeSegments(),
			objectParams[guiIndex].torus.mainRadius,
			oldMesh->getTubeRadius());

		torus->createMesh(
			torus->getVertices(),
			torus->getIndices(),
			torus->getVerticesCount(),
			torus->getIndicesCount()
		);

		torus->setMainRadius(objectParams[guiIndex].torus.mainRadius);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = torus;
	}
	else if (!approximatelyEqual(objectParams[guiIndex].torus.tubeRadius, oldMesh->getTubeRadius(), 0.01f))
	{
		Torus* torus = new Torus(
			oldMesh->getMainSegments(),
			oldMesh->getTubeSegments(),
			oldMesh->getMainRadius(),
			objectParams[guiIndex].torus.tubeRadius);

		torus->createMesh(
			torus->getVertices(),
			torus->getIndices(),
			torus->getVerticesCount(),
			torus->getIndicesCount()
		);

		torus->setTubeRadius(objectParams[guiIndex].torus.tubeRadius);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = torus;
	}
	else if (!approximatelyEqual(objectParams[guiIndex].torus.tubeRadius, oldMesh->getTubeRadius(), 0.01f))
	{
		Torus* torus = new Torus(
			oldMesh->getMainSegments(),
			oldMesh->getTubeSegments(),
			oldMesh->getMainRadius(),
			objectParams[guiIndex].torus.tubeRadius);

		torus->createMesh(
			torus->getVertices(),
			torus->getIndices(),
			torus->getVerticesCount(),
			torus->getIndicesCount()
		);

		torus->setMainRadius(objectParams[guiIndex].torus.tubeRadius);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = torus;
	}
	else if (objectParams[guiIndex].torus.mainSegments != oldMesh->getMainSegments())
	{
		Torus* torus = new Torus(
			objectParams[guiIndex].torus.mainSegments,
			oldMesh->getTubeSegments(),
			oldMesh->getMainRadius(),
			oldMesh->getTubeRadius());

		torus->createMesh(
			torus->getVertices(),
			torus->getIndices(),
			torus->getVerticesCount(),
			torus->getIndicesCount()
		);

		torus->setMainSegments(objectParams[guiIndex].torus.mainSegments);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = torus;
	}
	else if (objectParams[guiIndex].torus.tubeSegments != oldMesh->getTubeSegments())
	{
		Torus* torus = new Torus(
			oldMesh->getMainSegments(),
			objectParams[guiIndex].torus.tubeSegments,
			oldMesh->getMainRadius(),
			oldMesh->getTubeRadius());

		torus->createMesh(
			torus->getVertices(),
			torus->getIndices(),
			torus->getVerticesCount(),
			torus->getIndicesCount()
		);

		torus->setTubeSegments(objectParams[guiIndex].torus.tubeSegments);

		delete m_meshes[meshIndex];
		m_meshes[meshIndex] = torus;
	}

	if (selectedShader == shader::TRIANG_TESS_SHADER)
		m_meshes[MESH::TORUS]->renderPatch(3, wireframeMode);
	else if (selectedShader == shader::SIMPLE_SHADER)
		m_meshes[MESH::TORUS]->renderMesh(wireframeMode);
}

/* loading the data for the m_meshes to render */
void Scene::loadSceneObjects()
{
	Cube* quadMeshCube = new Cube(CubeMeshType::QuadrilateralMesh);
	m_meshes.push_back(quadMeshCube);

	Cube* trianMeshCube = new Cube(CubeMeshType::TriangularMesh);
	m_meshes.push_back(trianMeshCube);

	Pyramid* pyramid = new Pyramid();
	m_meshes.push_back(pyramid);

	Icosahedron* sphere = new Icosahedron(1.f, 0);

	sphere->setSubdivision(0);
	sphere->setRadius(1.f);
	sphere->setMiddlepoints(1.f, 1.f, 1.f);

	sphere->createMesh(
		sphere->getVertices(),
		sphere->getIndices(),
		sphere->getVertexCount(),
		sphere->getIndexCount());

	m_meshes.push_back(sphere);

	Prism* cylinder = new Prism();

	cylinder->setSectorCount(cylinder->getSectorCount());
	cylinder->setStackCount(cylinder->getStackCount());
	cylinder->setBaseRadius(cylinder->getBaseRadius());
	cylinder->setTopRadius(cylinder->getTopRadius());
	cylinder->setHeight(cylinder->getHeight());

	cylinder->createMesh(
		cylinder->getVertices(),
		cylinder->getIndices(),
		cylinder->getVertexCount(),
		cylinder->getIndexCount()
	);

	m_meshes.push_back(cylinder);

	Torus* torus = new Torus(20, 20, 0.5f, 0.2f);

	torus->setMainRadius(torus->getMainRadius());
	torus->setTubeRadius(torus->getTubeRadius());
	torus->setMainSegments(torus->getMainSegments());
	torus->setTubeSegments(torus->getTubeSegments());

	torus->createMesh(
		torus->getVertices(),
		torus->getIndices(),
		torus->getVerticesCount(),
		torus->getIndicesCount()
	);

	m_meshes.push_back(torus);
}