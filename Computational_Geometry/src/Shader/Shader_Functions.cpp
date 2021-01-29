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

void Shader::createFromFiles(const char* vertexLocation, const char* tcsLocation, const char* tesLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	std::string tessCSString = readFile(tcsLocation);
	std::string tessESString = readFile(tesLocation);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	const char* tessCSCode = tessCSString.c_str();
	const char* tessEVCode = tessESString.c_str();

	compileShader(vertexCode, tessCSCode, tessEVCode, fragmentCode);
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

void Shader::compileShader(const char* vertexCode, const char* tcsCode, const char* tesCode, const char* fragmentCode)
{
	m_shaderID = glCreateProgram();

	if (!m_shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	addShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(m_shaderID, tcsCode, GL_TESS_CONTROL_SHADER);
	addShader(m_shaderID, tesCode, GL_TESS_EVALUATION_SHADER);
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

	/* uniform matrices */
	uniformModelMatrix = glGetUniformLocation(m_shaderID, "model");
	uniformProjectionMatrix = glGetUniformLocation(m_shaderID, "projection");

	/* uniform triang tcs */
	uniformTriangInnerLevel = glGetUniformLocation(m_shaderID, "triangInnerLevel");
	uniformTriangOuterLevel1 = glGetUniformLocation(m_shaderID, "triangOuterLevel1");
	uniformTriangOuterLevel2 = glGetUniformLocation(m_shaderID, "triangOuterLevel2");
	uniformTriangOuterLevel3 = glGetUniformLocation(m_shaderID, "triangOuterLevel3");

	/* uniform quad tcs */
	uniformQuadInnerLevel1 = glGetUniformLocation(m_shaderID, "quadInnerLevel1");
	uniformQuadInnerLevel2 = glGetUniformLocation(m_shaderID, "quadInnerLevel2");
	uniformQuadOuterLevel1 = glGetUniformLocation(m_shaderID, "quadOuterLevel1");
	uniformQuadOuterLevel2 = glGetUniformLocation(m_shaderID, "quadOuterLevel2");
	uniformQuadOuterLevel3 = glGetUniformLocation(m_shaderID, "quadOuterLevel3");
	uniformQuadOuterLevel4 = glGetUniformLocation(m_shaderID, "quadOuterLevel4");

	/* uniform color picker */
	uniformPickedColor = glGetUniformLocation(m_shaderID, "pickedColor");

	/* uniform color mode */
	uniformColorMode = glGetUniformLocation(m_shaderID, "colorMode");

	/* barycentric coordinates colors */
	uniformBarycentricColorX = glGetUniformLocation(m_shaderID, "tessCoord_x_color");
	uniformBarycentricColorY = glGetUniformLocation(m_shaderID, "tessCoord_y_color");
	uniformBarycentricColorZ = glGetUniformLocation(m_shaderID, "tessCoord_z_color");
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