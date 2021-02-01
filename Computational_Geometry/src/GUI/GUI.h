#pragma once

#pragma warning(push, 0)

#include "../../Dependencies/imgui/imgui_impl_glfw.h"
#include "../../Dependencies/imgui/imgui_impl_opengl3.h"
#include "../../Dependencies/imgui/imgui.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#pragma warning(pop)
#include <map>
#include <iostream>
#include <vector>
#include <fstream>

#include "../Shader/Shader.h"

/* editable radiuses from user for the subdivided m_vertices (middlepoint) */
struct MiddlepointsRadius
{
	float v1{ 1.f };
	float v2{ 1.f };
	float v3{ 1.f };
};

/* Params of the objects in the GUI */
struct ObjectGUIParams {
	bool toVisualize{ false };
	int selectedShader{ 0 };

	/* Affine Transfomations */
	float xScale{ 1.0f };
	float yScale{ 1.0f };
	float zScale{ 1.0f };
	float overallScale{ 1.0f };

	float xRot{ 0.f };
	float yRot{ 0.f };
	float zRot{ 0.f };
	bool autoRotX{ false };
	bool autoRotY{ false };
	bool autoRotZ{ false };
	float rotSpeed{ 0.f };
	float increment{ 0.f };

	float xPos{ 0.f };
	float yPos{ 0.f };
	float zPos{ -2.5f };

	/* barycentric color, 0-red 1-green 2-blue */
	int channelOrder{ 0 };
	int x_tess_color{ 0 };
	int y_tess_color{ 1 };
	int z_tess_color{ 2 };

	struct
	{
		MiddlepointsRadius midpointRadius;
		int subdivisionLevel{ 0 };
		float radius{ 1.f };
	}icosahedron;

	struct
	{
		int sectorCount{ 3 };
		int stackCount{ 1 };
		float baseRadius{ 1.f };
		float topRadius{ 1.f };
		float height{ 1.f };
	}prism;

	struct
	{
		float mainRadius{ 0.5f };
		float tubeRadius{ 0.2f };
		int	mainSegments{ 20 };
		int tubeSegments{ 20 };
	}torus;

	/* colors */
	int colorMode{ 0 };
	glm::vec4 pickedColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
};

/* editable data from user for tessellation */
struct TessellationGUIParams {
	int selectedShader{ 0 };

	int outerLevel1{ 1 };
	int	outerLevel2{ 1 };
	int	outerLevel3{ 1 };
	int	outerLevel4{ 1 };
	int	innerLevel1{ 1 };
	int	innerLevel2{ 1 };

	bool wireframeMode{ false };
};

namespace GUI_OBJ
{
	constexpr unsigned int CUBE = 0U;
	constexpr unsigned int PYRAMID = 1U;
	constexpr unsigned int ICOSAHEDRON = 2U;
	constexpr unsigned int PRISM = 3U;
	constexpr unsigned int TORUS = 4U;
};

class GUI {
public:
	GUI()
	{
		checkCache();
	}

	GUI(float t_aspectRatio, int t_width, int t_height) : m_aspectRatio{ t_aspectRatio }, m_width{ t_width }, m_height{ t_height }
	{
		checkCache();
	}

	~GUI();

	void setupContext(GLFWwindow* window) const;
	void initFrame() const;
	void renderData() const;
	void destroyContext() const;

	void objectsPanel();
	void shaderPanel();

	void menuBar();

	void checkCache();
	bool* getCache() const { return &m_cache; }

	/* getters */
	std::map<int, ObjectGUIParams>& getObjectGUIParams();
	const TessellationGUIParams& getTessellationGUIParams() const;

private:
	void disableAllShapes();

	/* imgui.ini */
	static bool m_cache;

	/* window data */
	float m_aspectRatio{};
	int m_width{};
	int m_height{};

	/* handle objects panel*/
	int m_objectsIndices{ 0 };

	/* hold objects GUI params */
	std::map<int, ObjectGUIParams> m_objectParams{};

	/* handle tess panel */
	bool m_tessAllLevels{ false };
	int m_stepSize{ 1 };

	/* hold tess GUI params*/
	TessellationGUIParams m_tessParams{};

	/******/
	int selection{ 0 };
};
