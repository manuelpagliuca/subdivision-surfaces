#include "Scene.h"

Scene::Scene(const glm::mat4& t_projection)
{
	m_projectionMatrix = t_projection;
}

/* render the scene, using the user-input params */
void Scene::renderScene(const float deltaTime, std::map<int, ObjectGUIParams>& objectParams, const TessellationGUIParams& tessParams)
{
	/* Get the uniform locations */
	getUniformLocations(tessParams);

	/* handle objects */
	for (unsigned i = 0; i < objectParams.size(); ++i)
	{
		/* update the increment */
		objectParams[i].increment += deltaTime * objectParams[i].rotSpeed;

		/* use the selected shader (shader panel) */
		m_shaders[tessParams.selectedShader]->useShader();

		/* visualize the selected object */
		if (objectParams[i].toVisualize)
		{
			/* translation */
			m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(objectParams[i].xPos, 0.0f, 0.0f));
			m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.0f, objectParams[i].yPos, 0.0f));
			m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.0f, 0.0f, objectParams[i].zPos));

			/* rotation */
			m_modelMatrix = glm::rotate(m_modelMatrix, objectParams[i].autoRotX ? objectParams[i].xRot + objectParams[i].increment : objectParams[i].xRot, ROT::AXIS_X);
			m_modelMatrix = glm::rotate(m_modelMatrix, objectParams[i].autoRotY ? objectParams[i].yRot + objectParams[i].increment : objectParams[i].yRot, ROT::AXIS_Y);
			m_modelMatrix = glm::rotate(m_modelMatrix, objectParams[i].autoRotZ ? objectParams[i].zRot + objectParams[i].increment : objectParams[i].zRot, ROT::AXIS_Z);

			/* scaling */
			m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(objectParams[i].overallScale, objectParams[i].overallScale, objectParams[i].overallScale));
			m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(objectParams[i].xScale, 1.0f, 1.0f));
			m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(1.0f, objectParams[i].yScale, 1.0f));
			m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(1.0f, 1.0f, objectParams[i].zScale));

			// send transformation matrices
			glUniformMatrix4fv(uniformModelMatrix, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
			glUniformMatrix4fv(uniformProjectionMatrix, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

			if (tessParams.selectedShader == shader::TRIANG_TESS_SHADER)
			{
				// send triang-tessellation levels
				glUniform1f(uniformTriangTessInnerLevel1, static_cast<float>(tessParams.innerLevel1));
				glUniform1f(uniformTriangTessOuterLevel1, static_cast<float>(tessParams.outerLevel1));
				glUniform1f(uniformTriangTessOuterLevel2, static_cast<float>(tessParams.outerLevel2));
				glUniform1f(uniformTriangTessOuterLevel3, static_cast<float>(tessParams.outerLevel3));

				// send color for barycentric x-coord
				glUniform1i(uniformBarycentricColorX, objectParams[i].x_tess_color);
				glUniform1i(uniformBarycentricColorY, objectParams[i].y_tess_color);
				glUniform1i(uniformBarycentricColorZ, objectParams[i].z_tess_color);
			}

			if (tessParams.selectedShader == shader::QUADS_TESS_SHADER)
			{
				// send quad-tessellation levels
				glUniform1f(uniformQuadTessInnerLevel1, static_cast<float>(tessParams.innerLevel1));
				glUniform1f(uniformQuadTessInnerLevel2, static_cast<float>(tessParams.innerLevel2));
				glUniform1f(uniformQuadTessOuterLevel1, static_cast<float>(tessParams.outerLevel1));
				glUniform1f(uniformQuadTessOuterLevel2, static_cast<float>(tessParams.outerLevel2));
				glUniform1f(uniformQuadTessOuterLevel3, static_cast<float>(tessParams.outerLevel3));
				glUniform1f(uniformQuadTessOuterLevel4, static_cast<float>(tessParams.outerLevel4));
			}

			// send picked color
			glUniform4fv(uniformPickedColor, 1, glm::value_ptr(objectParams[i].pickedColor));

			// send color mode
			glUniform1i(uniformColorMode, objectParams[i].colorMode);

			if (tessParams.selectedShader == shader::SIMPLE_SHADER)
			{
				// send color for barycentric x-coord
				glUniform1i(uniformBarycentricColorX, 0);
				glUniform1i(uniformBarycentricColorY, 1);
				glUniform1i(uniformBarycentricColorZ, 2);
			}

			switch (i)
			{
			case GUI_OBJ::CUBE:
				if (tessParams.selectedShader == shader::QUADS_TESS_SHADER)
					m_meshes[MESH::QUAD_CUBE]->renderPatch(4, tessParams.wireframeMode);
				else if (tessParams.selectedShader == shader::TRIANG_TESS_SHADER)
					m_meshes[MESH::TRIAN_CUBE]->renderPatch(3, tessParams.wireframeMode);
				else if (tessParams.selectedShader == shader::SIMPLE_SHADER)
					m_meshes[MESH::TRIAN_CUBE]->renderMesh(tessParams.wireframeMode);
				break;

			case GUI_OBJ::PYRAMID:
				if (tessParams.selectedShader == shader::TRIANG_TESS_SHADER)
					m_meshes[MESH::PYRAMID]->renderPatch(3, tessParams.wireframeMode);
				else if (tessParams.selectedShader == shader::SIMPLE_SHADER)
					m_meshes[MESH::PYRAMID]->renderMesh(tessParams.wireframeMode);
				break;

			case GUI_OBJ::ICOSAHEDRON:
				renderIcosahedron(objectParams, tessParams.wireframeMode, GUI_OBJ::ICOSAHEDRON, MESH::ICOSAHEDRON, tessParams.selectedShader);
				break;

			case GUI_OBJ::PRISM:
				renderPrism(objectParams, tessParams.wireframeMode, GUI_OBJ::PRISM, MESH::PRISM, tessParams.selectedShader);
				break;

			case GUI_OBJ::TORUS:
				renderTorus(objectParams, tessParams.wireframeMode, GUI_OBJ::TORUS, MESH::TORUS, tessParams.selectedShader);
				break;
			}
		}

		m_modelMatrix = glm::mat4{ 1.f };
	}
}

/* retrieve the locations of uniforms */
void Scene::getUniformLocations(const TessellationGUIParams& tessParams)
{
	/* model, view, projection */
	uniformModelMatrix = m_shaders[tessParams.selectedShader]->getModelLocation();
	uniformProjectionMatrix = m_shaders[tessParams.selectedShader]->getProjectionLocation();

	/* triangular tessellation levels */
	uniformTriangTessInnerLevel1 = m_shaders[tessParams.selectedShader]->getLocationTriangInnerLevel1();
	uniformTriangTessOuterLevel1 = m_shaders[tessParams.selectedShader]->getLocationTriangOuterLevel1();
	uniformTriangTessOuterLevel2 = m_shaders[tessParams.selectedShader]->getLocationTriangOuterLevel2();
	uniformTriangTessOuterLevel3 = m_shaders[tessParams.selectedShader]->getLocationTriangOuterLevel3();

	/* quadrilateral tessellation levels */
	uniformQuadTessInnerLevel1 = m_shaders[tessParams.selectedShader]->getLocationQuadInnerLevel1();
	uniformQuadTessInnerLevel2 = m_shaders[tessParams.selectedShader]->getLocationQuadInnerLevel2();
	uniformQuadTessOuterLevel1 = m_shaders[tessParams.selectedShader]->getLocationQuadOuterLevel1();
	uniformQuadTessOuterLevel2 = m_shaders[tessParams.selectedShader]->getLocationQuadOuterLevel2();
	uniformQuadTessOuterLevel3 = m_shaders[tessParams.selectedShader]->getLocationQuadOuterLevel3();
	uniformQuadTessOuterLevel4 = m_shaders[tessParams.selectedShader]->getLocationQuadOuterLevel4();

	/* uniform for colors */
	uniformPickedColor = m_shaders[tessParams.selectedShader]->getLocationPickedColor();
	uniformColorMode = m_shaders[tessParams.selectedShader]->getLocationColorMode();

	/* uniform for color of barycentric coordinates */
	uniformBarycentricColorX = m_shaders[tessParams.selectedShader]->getLocationBarycentricColorX();
	uniformBarycentricColorY = m_shaders[tessParams.selectedShader]->getLocationBarycentricColorY();
	uniformBarycentricColorZ = m_shaders[tessParams.selectedShader]->getLocationBarycentricColorZ();
}

/* loading the m_shaders to use rendering */
void Scene::loadSceneShaders()
{
	/* vertex-fragment shader */
	m_shaders.push_back(new Shader(source::vShader, source::fShader));
}