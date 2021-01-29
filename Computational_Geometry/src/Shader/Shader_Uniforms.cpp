#include "Shader.h"

const GLuint& Shader::getProjectionLocation() const
{
	return uniformProjectionMatrix;
}

const GLuint& Shader::getModelLocation() const
{
	return uniformModelMatrix;
}

const GLuint& Shader::getLocationTriangInnerLevel1() const
{
	return uniformTriangInnerLevel;
}

const GLuint& Shader::getLocationTriangOuterLevel1() const
{
	return uniformTriangOuterLevel1;
}

const GLuint& Shader::getLocationTriangOuterLevel2() const
{
	return uniformTriangOuterLevel2;
}

const GLuint& Shader::getLocationTriangOuterLevel3() const
{
	return uniformTriangOuterLevel3;
}

const GLuint& Shader::getLocationQuadInnerLevel1() const
{
	return uniformQuadInnerLevel1;
}

const GLuint& Shader::getLocationQuadInnerLevel2() const
{
	return uniformQuadInnerLevel2;
}

const GLuint& Shader::getLocationQuadOuterLevel1() const
{
	return uniformQuadOuterLevel1;
}

const GLuint& Shader::getLocationQuadOuterLevel2() const
{
	return uniformQuadOuterLevel2;
}

const GLuint& Shader::getLocationQuadOuterLevel3() const
{
	return uniformQuadOuterLevel3;
}

const GLuint& Shader::getLocationQuadOuterLevel4() const
{
	return uniformQuadOuterLevel4;
}

const GLuint& Shader::getLocationPickedColor() const
{
	return uniformPickedColor;
}

const GLuint& Shader::getLocationColorMode() const
{
	return uniformColorMode;
}

const GLuint& Shader::getLocationBarycentricColorX() const
{
	return uniformBarycentricColorX;
}

const GLuint& Shader::getLocationBarycentricColorY() const
{
	return uniformBarycentricColorY;
}

const GLuint& Shader::getLocationBarycentricColorZ() const
{
	return uniformBarycentricColorZ;
}