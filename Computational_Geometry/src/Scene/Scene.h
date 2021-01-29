#pragma once

#include <vector>
#include <algorithm>
#include <map>

#pragma warning(push, 0)
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#pragma warning(pop)

#include "../Shader/Shader.h"
#include "../GUI/GUI.h"
#include "../Mesh/Mesh.h"
#include "../Mesh/Objects/Icosahedron.h"
#include "../Mesh/Objects/Cube.h"
#include "../Mesh/Objects/Prism.h"
#include "../Mesh/Objects/Pyramid.h"
#include "../Mesh/Objects/Torus.h"

namespace ROT {
	const glm::vec3 AXIS_X = glm::vec3(1.f, 0.f, 0.f);
	const glm::vec3 AXIS_Y = glm::vec3(0.f, 1.f, 0.f);
	const glm::vec3 AXIS_Z = glm::vec3(0.f, 0.f, 1.f);
}

namespace MESH {
	constexpr unsigned int QUAD_CUBE = 0U;
	constexpr unsigned int TRIAN_CUBE = 1U;
	constexpr unsigned int PYRAMID = 2U;
	constexpr unsigned int ICOSAHEDRON = 3U;
	constexpr unsigned int PRISM = 4U;
	constexpr unsigned int TORUS = 5U;
}

class Scene {
public:
	/* ctor/dtor */
	Scene() = default;
	Scene(const glm::mat4& t_projection);
	~Scene() = default;

	/* member function */
	void loadSceneShaders();
	void loadSceneObjects();
	void renderScene(const float deltaTime, std::map<int, ObjectGUIParams>& t_objectParams, const TessellationGUIParams& t_tessParams);

	/* complex shapes */
	void renderIcosahedron(std::map<int, ObjectGUIParams>& objectParams, const bool wireframeMode, const unsigned guiIndex, const unsigned meshIndex, const int selectedShader);
	void renderPrism(std::map<int, ObjectGUIParams>& objectParams, const bool wireframeMode, const unsigned guiIndex, const unsigned meshIndex, const int selectedShader);
	void renderTorus(std::map<int, ObjectGUIParams>& objectParams, const bool wireframeMode, const unsigned guiIndex, const unsigned meshIndex, const int selectedShader);

	/* getters */
	void getUniformLocations(const TessellationGUIParams& t_tessParams);
private:
	std::vector<Shader*> m_shaders;
	std::vector<Mesh*> m_meshes;

	/* matrices */
	glm::mat4 m_projectionMatrix{ 1.f };
	glm::mat4 m_modelMatrix{ 1.f };

	/* uniforms */
	GLuint uniformProjectionMatrix{ 0 };
	GLuint uniformModelMatrix{ 0 };

	GLuint uniformTriangTessInnerLevel1{ 0 };
	GLuint uniformTriangTessOuterLevel1{ 0 };
	GLuint uniformTriangTessOuterLevel2{ 0 };
	GLuint uniformTriangTessOuterLevel3{ 0 };

	GLuint uniformQuadTessInnerLevel1{ 0 };
	GLuint uniformQuadTessInnerLevel2{ 0 };
	GLuint uniformQuadTessOuterLevel1{ 0 };
	GLuint uniformQuadTessOuterLevel2{ 0 };
	GLuint uniformQuadTessOuterLevel3{ 0 };
	GLuint uniformQuadTessOuterLevel4{ 0 };

	GLuint uniformPickedColor{ 0 };
	GLuint uniformColorMode{ 0 };

	GLuint uniformBarycentricColorX{ 0 };
	GLuint uniformBarycentricColorY{ 0 };
	GLuint uniformBarycentricColorZ{ 0 };
};