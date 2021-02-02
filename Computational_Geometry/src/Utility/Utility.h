#pragma once

#pragma warning(push, 0)
#include "../../Dependencies/imgui/imgui_impl_glfw.h"
#include "../../Dependencies/imgui/imgui_impl_opengl3.h"
#include "../../Dependencies/imgui/imgui.h"
#pragma warning(pop)

#include "../Mesh/Mesh.h"
#include "../Shader/Shader.h"
#include "../GUI/GUI.h"
#include "../GUI/Window.h"

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#define ASSERT(x) if(!(x)) __debugbreak();

#define BUFFER_OFFSET_NULL(x) (const void *) (x)

#define GLCall(x)	GLClearError();\
					x;\
					ASSERT(GLLogCall(#x, __FILE__, __LINE__))

inline bool approximatelyEqual(const float& a, const float& b, const float& epsilon)
{
	return (std::fabs(a - b) <= (std::max(std::fabs(a), std::fabs(b)) * epsilon));
}

/*static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL_Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}*/
