#include "GUI.h"

// Init static variable for caching parameters
bool GUI::m_cache = false;

/* panel for editing object structure features */
void GUI::objectsPanel()
{
	ImGuiWindowFlags window_flags{ ImGuiWindowFlags_NoResize };
	ImGui::SetNextWindowSize(ImVec2(400.f, 600.f));
	ImGui::SetNextWindowPos(ImVec2(1450.f, 50.f), ImGuiCond_FirstUseEver);
	ImGui::Begin("Object Panel", nullptr, window_flags);
	ImGui::Separator(); ImGui::SameLine(140); ImGui::Text("Select object"); ImGui::NewLine();

	ImGui::Combo("", &m_objectsIndices, "Cube\0Pyramid\0Icosahedron\0Prism\0Torus\0");

	switch (m_objectsIndices)
	{
	case 0:
		disableAllShapes();
		m_objectParams[GUI_OBJ::CUBE].toVisualize = true;
		break;
	case 1:
		disableAllShapes();
		m_objectParams[GUI_OBJ::PYRAMID].toVisualize = true;
		break;
	case 2:
		disableAllShapes();
		m_objectParams[GUI_OBJ::ICOSAHEDRON].toVisualize = true;
		break;
	case 3:
		disableAllShapes();
		m_objectParams[GUI_OBJ::PRISM].toVisualize = true;
		break;
	case 4:
		disableAllShapes();
		m_objectParams[GUI_OBJ::TORUS].toVisualize = true;
		break;
	}

	for (unsigned int i = 0; i < m_objectParams.size(); i++) {
		if (m_objectParams[i].toVisualize)
		{
			constexpr int labelSpace = 280;
			ImGui::NewLine(); ImGui::Separator(); ImGui::SameLine(120); ImGui::Text("Affine Transformations"); ImGui::NewLine();

			/* rotations */
			ImGui::SliderFloat("x", &m_objectParams[i].xRot, -5.f, 5.0f); ImGui::SameLine(labelSpace); ImGui::Text("Rot-X"); ImGui::SameLine();
			ImGui::Checkbox("Auto-X", &m_objectParams[i].autoRotX);

			ImGui::SliderFloat("y", &m_objectParams[i].yRot, -5.f, 5.0f); ImGui::SameLine(labelSpace); ImGui::Text("Rot-Y"); ImGui::SameLine();
			ImGui::Checkbox("Auto-Y", &m_objectParams[i].autoRotY);

			ImGui::SliderFloat("z", &m_objectParams[i].zRot, -5.f, 5.0f); ImGui::SameLine(labelSpace); ImGui::Text("Rot-Z"); ImGui::SameLine();
			ImGui::Checkbox("Auto-Z", &m_objectParams[i].autoRotZ);
			
			ImGui::SliderFloat("rotSpeed", &m_objectParams[i].rotSpeed, 0.f, 1.f); ImGui::SameLine(labelSpace); ImGui::Text("Rotation Speed");
			ImGui::NewLine();

			/* scalings */
			ImGui::SliderFloat("scale", &m_objectParams[i].overallScale, 0.f, 2.0f);	ImGui::SameLine(labelSpace); ImGui::Text("Scale");
			ImGui::SliderFloat("scale-x", &m_objectParams[i].xScale, 0.f, 2.0f); ImGui::SameLine(labelSpace); ImGui::Text("Scale-X");
			ImGui::SliderFloat("scale-y", &m_objectParams[i].yScale, 0.f, 2.0f); ImGui::SameLine(labelSpace); ImGui::Text("Scale-Y");
			ImGui::SliderFloat("scale-z", &m_objectParams[i].zScale, 0.f, 2.0f); ImGui::SameLine(labelSpace); ImGui::Text("Scale-Z");
			ImGui::NewLine();

			/* translations */
			ImGui::SliderFloat("pos-x", &m_objectParams[i].xPos, -.5f, +0.5f); ImGui::SameLine(labelSpace); ImGui::Text("Pos-X");
			ImGui::SliderFloat("pos-y", &m_objectParams[i].yPos, -.5f, +0.5f); ImGui::SameLine(labelSpace); ImGui::Text("Pos-Y");
			ImGui::SliderFloat("pos-z", &m_objectParams[i].zPos, -5.0f, 0.1f); ImGui::SameLine(labelSpace); ImGui::Text("Pos-Z");
			ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(120);

			if (ImGui::Button("Reset transformations"))
			{
				m_objectParams[i].xRot = 0.f;
				m_objectParams[i].yRot = 0.f;
				m_objectParams[i].zRot = 0.f;
				m_objectParams[i].overallScale = 1.f;
				m_objectParams[i].xScale = 1.f;
				m_objectParams[i].yScale = 1.f;
				m_objectParams[i].zScale = 1.f;
				m_objectParams[i].xPos = 0.f;
				m_objectParams[i].yPos = 0.f;
				m_objectParams[i].zPos = -2.5f;
				m_objectParams[i].rotSpeed = 0.f;
				m_objectParams[i].autoRotX = false;
				m_objectParams[i].autoRotY = false;
				m_objectParams[i].autoRotZ = false;
			}
			ImGui::NewLine();

			if (i == GUI_OBJ::ICOSAHEDRON)
			{
				ImGui::NewLine(); ImGui::Separator(); ImGui::SameLine(140); ImGui::Text("Icosahedron settings"); ImGui::NewLine();
				constexpr int labelSpace = 280;

				ImGui::SliderInt("subdLevel", &m_objectParams[i].icosahedron.subdivisionLevel, 0, 4); ImGui::SameLine(labelSpace); ImGui::Text("Subdivision");
				ImGui::SliderFloat("radIcoVert", &m_objectParams[i].icosahedron.radius, 0.f, 10.f); ImGui::SameLine(labelSpace); ImGui::Text("Icosahedron\n vertices");
				ImGui::SliderFloat("radMid1", &m_objectParams[i].icosahedron.midpointRadius.v1, -5.f, 5.f); ImGui::SameLine(labelSpace); ImGui::Text("Midpoints 1");
				ImGui::SliderFloat("radMid2", &m_objectParams[i].icosahedron.midpointRadius.v2, -5.f, 5.f); ImGui::SameLine(labelSpace); ImGui::Text("Midpoints 2");
				ImGui::SliderFloat("radMid3", &m_objectParams[i].icosahedron.midpointRadius.v3, -5.f, 5.f); ImGui::SameLine(labelSpace); ImGui::Text("Midpoints 3");

				ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(180);
				if (ImGui::Button("Reset"))
				{
					m_objectParams[i].icosahedron.subdivisionLevel = 0;
					m_objectParams[i].icosahedron.radius = 1.f;
					m_objectParams[i].icosahedron.midpointRadius.v1 = 1.f;
					m_objectParams[i].icosahedron.midpointRadius.v2 = 1.f;
					m_objectParams[i].icosahedron.midpointRadius.v3 = 1.f;
				}
				ImGui::NewLine();
			}
			else if (i == GUI_OBJ::PRISM)
			{
				ImGui::NewLine(); ImGui::Separator(); ImGui::SameLine(140); ImGui::Text("Prism settings"); ImGui::NewLine();
				constexpr int labelSpace = 280;

				ImGui::SliderInt("sectorCount", &m_objectParams[i].prism.sectorCount, 3, 100); ImGui::SameLine(labelSpace); ImGui::Text("Sector count");
				ImGui::SliderInt("stackCount", &m_objectParams[i].prism.stackCount, 1, 10); ImGui::SameLine(labelSpace); ImGui::Text("Stack count");
				ImGui::SliderFloat("baseRadius", &m_objectParams[i].prism.baseRadius, 0.f, 10.f); ImGui::SameLine(labelSpace); ImGui::Text("Base radius");
				ImGui::SliderFloat("topRadius", &m_objectParams[i].prism.topRadius, 0.f, 10.f); ImGui::SameLine(labelSpace); ImGui::Text("Top radius");
				ImGui::SliderFloat("height", &m_objectParams[i].prism.height, 0.1f, 10.f); ImGui::SameLine(labelSpace); ImGui::Text("Height");

				ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(180);
				if (ImGui::Button("Reset"))
				{
					m_objectParams[i].prism.sectorCount = 3;
					m_objectParams[i].prism.stackCount = 1;
					m_objectParams[i].prism.baseRadius = 1.f;
					m_objectParams[i].prism.topRadius = 1.f;
					m_objectParams[i].prism.height = 1.f;
				}
				ImGui::NewLine();
			}
			else if (i == GUI_OBJ::TORUS)
			{
				ImGui::NewLine(); ImGui::Separator(); ImGui::SameLine(140); ImGui::Text("Torus settings"); ImGui::NewLine();
				constexpr int labelSpace = 280;

				ImGui::SliderFloat("Main radius", &m_objectParams[i].torus.mainRadius, 0.1f, 3.f); ImGui::SameLine(labelSpace); ImGui::Text("Main radius");
				ImGui::SliderFloat("Tube radius", &m_objectParams[i].torus.tubeRadius, 0.1f, 3.f); ImGui::SameLine(labelSpace); ImGui::Text("Tube radius");
				ImGui::SliderInt("Main Segments", &m_objectParams[i].torus.mainSegments, 3, 100); ImGui::SameLine(labelSpace); ImGui::Text("Main segments");
				ImGui::SliderInt("Tube Segments", &m_objectParams[i].torus.tubeSegments, 3, 100); ImGui::SameLine(labelSpace); ImGui::Text("Tube segments");

				ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(180);
				if (ImGui::Button("Reset"))
				{
					m_objectParams[i].torus.mainRadius = .5f;
					m_objectParams[i].torus.tubeRadius = .5f;
					m_objectParams[i].torus.mainSegments = 20;
					m_objectParams[i].torus.tubeSegments = 20;
				}

				ImGui::NewLine();
			}

			if (m_tessParams.selectedShader == shader::TRIANG_TESS_SHADER)
			{
				ImGui::Separator(); ImGui::SameLine(140); ImGui::Text("Color settings");
				ImGui::NewLine(); ImGui::SameLine(90); ImGui::RadioButton("Interpolation", &m_objectParams[i].colorMode, 0);
				ImGui::SameLine(); ImGui::RadioButton("Solid color", &m_objectParams[i].colorMode, 1);
				ImGui::NewLine();

				if (m_objectParams[i].colorMode)
					ImGui::ColorEdit3("Color Picker", (float*)&m_objectParams[i].pickedColor);
				else
				{
					if (m_objectParams[i].colorMode)
						ImGui::ColorEdit3("Color Picker", (float*)&m_objectParams[i].pickedColor);
					else
					{
						constexpr int labelSpace = 120;
						ImGui::SameLine(labelSpace); ImGui::Text("Barycentric coordinates");
						ImGui::NewLine(); ImGui::NewLine();
						ImGui::SameLine(30); ImGui::Combo("Channel order", &selection, "RGB\0RBG\0GRB\0GBR\0BRG\0BGR\0");

						switch (selection)
						{
						case 0:	// RGB
							m_objectParams[i].x_tess_color = 0;
							m_objectParams[i].y_tess_color = 1;
							m_objectParams[i].z_tess_color = 2;
							break;
						case 1:	// RBG
							m_objectParams[i].x_tess_color = 0;
							m_objectParams[i].y_tess_color = 2;
							m_objectParams[i].z_tess_color = 1;
							break;
						case 2:	// GRB
							m_objectParams[i].x_tess_color = 1;
							m_objectParams[i].y_tess_color = 0;
							m_objectParams[i].z_tess_color = 2;
							break;
						case 3: // GBR
							m_objectParams[i].x_tess_color = 2;
							m_objectParams[i].y_tess_color = 0;
							m_objectParams[i].z_tess_color = 1;
							break;
						case 4: // BRG
							m_objectParams[i].x_tess_color = 1;
							m_objectParams[i].y_tess_color = 2;
							m_objectParams[i].z_tess_color = 0;
							break;
						case 5: // BGR
							m_objectParams[i].x_tess_color = 2;
							m_objectParams[i].y_tess_color = 1;
							m_objectParams[i].z_tess_color = 0;
							break;
						}
					}
				}
			}
		}
	}

	ImGui::End();
}

/* panel for edit the tessellation levels */
void GUI::tessPanel()
{
	ImGuiWindowFlags window_flags{ ImGuiWindowFlags_NoResize };
	ImGui::SetNextWindowSize(ImVec2(350.f, 280.f), 0);
	ImGui::SetNextWindowPos(ImVec2(50.f, 50.f), ImGuiCond_FirstUseEver);
	ImGui::Begin("Tessellation", NULL, window_flags);
	constexpr int textSpace = 250;

	if (m_tessParams.selectedShader == shader::TRIANG_TESS_SHADER)
	{
		ImGui::Checkbox("Show tessellation wireframe", &m_tessParams.wireframeMode);
		ImGui::SliderInt("inner", &m_tessParams.innerLevel1, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Inner Level");
		ImGui::SliderInt("outerTri1", &m_tessParams.outerLevel1, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Outer Level 1");
		ImGui::SliderInt("outerTri2", &m_tessParams.outerLevel2, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Outer Level 2");
		ImGui::SliderInt("outerTri3", &m_tessParams.outerLevel3, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Outer Level 3");

		ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(150);

		if (ImGui::Button("Reset"))
		{
			m_tessParams.innerLevel1 = 1;
			m_tessParams.innerLevel2 = 1;
			m_tessParams.outerLevel1 = 1;
			m_tessParams.outerLevel2 = 1;
			m_tessParams.outerLevel3 = 1;
			m_tessParams.outerLevel4 = 1;
		}

		ImGui::Separator();	ImGui::NewLine(); ImGui::Checkbox("Lock all levels", &m_tessAllLevels);

		if (m_tessAllLevels)
		{
			ImGui::NewLine(); ImGui::SliderInt("allTriaLevels", &m_stepSize, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("All Levels");
			m_tessParams.innerLevel1 = m_stepSize;
			m_tessParams.outerLevel1 = m_stepSize;
			m_tessParams.outerLevel2 = m_stepSize;
			m_tessParams.outerLevel3 = m_stepSize;
		}
	}
	else if (m_tessParams.selectedShader == shader::QUADS_TESS_SHADER)
	{
		if (m_objectParams[GUI_OBJ::CUBE].toVisualize)
		{
			ImGui::Checkbox("Wireframe", &m_tessParams.wireframeMode);
			ImGui::SliderInt("innerQuad1", &m_tessParams.innerLevel1, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Inner Level 1");
			ImGui::SliderInt("innerQuad2", &m_tessParams.innerLevel2, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Inner Level 2");
			ImGui::SliderInt("outerQuad1", &m_tessParams.outerLevel1, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Outer Level 1");
			ImGui::SliderInt("outerQuad2", &m_tessParams.outerLevel2, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Outer Level 2");
			ImGui::SliderInt("outerQuad3", &m_tessParams.outerLevel3, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Outer Level 3");
			ImGui::SliderInt("outerQuad4", &m_tessParams.outerLevel4, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("Outer Level 4");

			ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(150);

			if (ImGui::Button("Reset"))
			{
				m_tessParams.innerLevel1 = 1;
				m_tessParams.innerLevel2 = 1;
				m_tessParams.outerLevel1 = 1;
				m_tessParams.outerLevel2 = 1;
				m_tessParams.outerLevel3 = 1;
				m_tessParams.outerLevel4 = 1;
			}

			ImGui::Separator();	ImGui::NewLine(); ImGui::Checkbox("Lock all levels", &m_tessAllLevels);

			if (m_tessAllLevels)
			{
				ImGui::NewLine(); ImGui::SliderInt("allQuadLevels", &m_stepSize, 1, 20); ImGui::SameLine(textSpace); ImGui::Text("All Levels");
				m_tessParams.innerLevel1 = m_stepSize;
				m_tessParams.innerLevel2 = m_stepSize;
				m_tessParams.outerLevel1 = m_stepSize;
				m_tessParams.outerLevel2 = m_stepSize;
				m_tessParams.outerLevel3 = m_stepSize;
				m_tessParams.outerLevel4 = m_stepSize;
			}
		}
		else
		{
			ImGui::TextColored(ImVec4(1.0f, 0.f, 0.f, 1.f), "Quadrilateral primitive not available for\nthis object!");
		}
	}
	else
	{
		ImGui::SameLine(130); ImGui::TextColored(ImVec4(1.0f, 0.f, 0.f, 1.f), "TCS not found!");
	}
	ImGui::End();
}

/* panel for selecting the m_shaders */
void GUI::shaderPanel()
{
	ImGuiWindowFlags window_flags{ ImGuiWindowFlags_NoResize };
	ImGui::SetNextWindowSize(ImVec2(300.f, 100.f), 0);
	ImGui::SetNextWindowPos(ImVec2(50.f, 820.f), ImGuiCond_FirstUseEver);
	ImGui::Begin("Shaders", nullptr, window_flags);
	ImGui::Combo("ShaderType", &m_tessParams.selectedShader, "Simple VS-FS\0Triangle Tessellation\0Quad Tessellation\0");

	switch (m_tessParams.selectedShader)
	{
	case 0:
		m_tessParams.selectedShader = shader::SIMPLE_SHADER;
		ImGui::NewLine(); ImGui::Checkbox("Wireframe", &m_tessParams.wireframeMode);
		break;
	case 1:
		m_tessParams.selectedShader = shader::TRIANG_TESS_SHADER;
		break;
	case 2:
		m_tessParams.selectedShader = shader::QUADS_TESS_SHADER;
		break;
	}

	ImGui::End();
}

/* Handle menu bar */
void GUI::menuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				exit(1);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void GUI::checkCache()
{
	std::ifstream f{ "imgui.ini" };
	if (f.good())
		m_cache = true;
	else
		m_cache = false;
}

/* disable all shapes (private)*/
void GUI::disableAllShapes()
{
	for (size_t i = 0; i < m_objectParams.size(); i++)
		m_objectParams[i].toVisualize = false;
}

/* init of imgui */
void GUI::initFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	/* disable rounding graphics */
	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().ChildRounding = 0.0f;
	ImGui::GetStyle().FrameRounding = 0.0f;
	ImGui::GetStyle().GrabRounding = 0.0f;
	ImGui::GetStyle().PopupRounding = 0.0f;
	ImGui::GetStyle().ScrollbarRounding = 0.0f;
}

/* setting up the context on the m_window*/
void GUI::setupContext(GLFWwindow* m_window) const
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//(void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 430");
}

/* freeing up the memory */
void GUI::destroyContext() const
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

/* rendering the panels */
void GUI::renderData() const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/* return the data structure for object features*/
std::map<int, ObjectGUIParams>& GUI::getObjectGUIParams()
{
	return m_objectParams;
}

/* return the data structure for tessellation levels */
const TessellationGUIParams& GUI::getTessellationGUIParams() const
{
	return m_tessParams;
}

/* destructor */
GUI::~GUI()
{
	if (!m_cache)
	{
		remove("imgui.ini");
	}
}