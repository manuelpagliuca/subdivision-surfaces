#pragma once

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>

namespace shader {
	constexpr int UNSELECTED{ -1 };
	constexpr int SIMPLE_SHADER{ 0 };
	constexpr int TRIANG_TESS_SHADER{ 1 };
	constexpr int QUADS_TESS_SHADER{ 2 };
};

namespace source {
	inline const char* vShader = "Shaders/shader.vert";
	inline const char* fShader = "Shaders/shader.frag";
};

class Shader
{
public:
	/* ctor/dtor */
	Shader() = default;
	Shader(const char* vShader, const char* fShader)
	{
		createFromFiles(vShader, fShader);
	}

	~Shader();

	/* member functions */
	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation);
	std::string readFile(const char* fileLocation) const;
	void useShader() const;
	void clearShader();

	/* getters */
	const GLuint& getProjectionLocation() const;
	const GLuint& getModelLocation() const;
	const GLuint& getLocationTriangInnerLevel1() const;
	const GLuint& getLocationTriangOuterLevel1() const;
	const GLuint& getLocationTriangOuterLevel2() const;
	const GLuint& getLocationTriangOuterLevel3() const;
	const GLuint& getLocationQuadInnerLevel1() const;
	const GLuint& getLocationQuadInnerLevel2() const;
	const GLuint& getLocationQuadOuterLevel1() const;
	const GLuint& getLocationQuadOuterLevel2() const;
	const GLuint& getLocationQuadOuterLevel3() const;
	const GLuint& getLocationQuadOuterLevel4() const;
	const GLuint& getLocationPickedColor() const;
	const GLuint& getLocationColorMode() const;
	const GLuint& getLocationBarycentricColorX() const;
	const GLuint& getLocationBarycentricColorY() const;
	const GLuint& getLocationBarycentricColorZ() const;

private:
	/* private functions*/
	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(const GLuint& theProgram, const char* shaderCode, const GLenum& shaderType) const;

	/* program id */
	GLuint m_shaderID{};

	/* uniforms */
	GLuint uniformProjectionMatrix{};
	GLuint uniformModelMatrix{};

	GLuint uniformTriangInnerLevel{};
	GLuint uniformTriangOuterLevel1{};
	GLuint uniformTriangOuterLevel2{};
	GLuint uniformTriangOuterLevel3{};

	GLuint uniformQuadInnerLevel1{};
	GLuint uniformQuadInnerLevel2{};
	GLuint uniformQuadOuterLevel1{};
	GLuint uniformQuadOuterLevel2{};
	GLuint uniformQuadOuterLevel3{};
	GLuint uniformQuadOuterLevel4{};

	GLuint uniformPickedColor{};
	GLuint uniformColorMode{};

	GLuint uniformBarycentricColorX{};
	GLuint uniformBarycentricColorY{};
	GLuint uniformBarycentricColorZ{};
};