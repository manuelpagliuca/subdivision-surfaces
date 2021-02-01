#include "Shader.h"

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* fileLocation) const
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	m_shaderID = glCreateProgram();

	if (!m_shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	addShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformProjectionMatrix = glGetUniformLocation(m_shaderID, "projection");
	uniformModelMatrix = glGetUniformLocation(m_shaderID, "model");
}

void Shader::addShader(const GLuint& theProgram, const char* shaderCode, const GLenum& shaderType) const
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = static_cast<GLint>(strlen(shaderCode));

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cerr << "Error compiling the " << shaderType << "shader: " << eLog << "\n";
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::useShader() const
{
	glUseProgram(m_shaderID);
}

void Shader::clearShader()
{
	if (m_shaderID != 0)
	{
		glDeleteProgram(m_shaderID);
		m_shaderID = 0;
	}

	uniformModelMatrix = 0;
	uniformProjectionMatrix = 0;

	uniformTriangInnerLevel = 0;
	uniformTriangOuterLevel1 = 0;
	uniformTriangOuterLevel1 = 0;
	uniformTriangOuterLevel2 = 0;
	uniformTriangOuterLevel3 = 0;

	uniformQuadInnerLevel1 = 0;
	uniformQuadInnerLevel2 = 0;
	uniformQuadOuterLevel1 = 0;
	uniformQuadOuterLevel2 = 0;
	uniformQuadOuterLevel3 = 0;
	uniformQuadOuterLevel4 = 0;

	uniformPickedColor = 0;
	uniformColorMode = 0;

	uniformBarycentricColorX = 0;
	uniformBarycentricColorY = 0;
	uniformBarycentricColorZ = 0;
}

Shader::~Shader()
{
	clearShader();
}