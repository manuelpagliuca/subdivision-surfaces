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

// Enable to select the fullscreen mode and the caching of the gui positions.
static int runSettingsWindow(Window& resWindow)
{
	if (!resWindow.initialise())
	{
		std::cerr << "Error initialising the boot window.\n";
		resWindow.~Window();
		return EXIT_FAILURE;
	}

	GUI resGui{};
	resGui.setupContext(resWindow.getWindowObject());

	while (!resWindow.getShouldClose())
	{
		glfwPollEvents();

		glClearColor(0.f, 0.f, 0.f, 1.f);

		resGui.initFrame();

		ImGuiWindowFlags window_flags{
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoNav |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoScrollbar
		};

		ImGui::SetNextWindowSize(ImVec2(400.f, 100.f));
		ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_FirstUseEver);

		ImGui::Begin("Settings", nullptr, window_flags);

		ImGui::SameLine(30);
		ImGui::Text("The risolution will be 1900x1080 and \napplication will be windowed.");
		ImGui::NewLine();
		ImGui::Checkbox("Cache", resGui.getCache());
		ImGui::SameLine(160);

		if (ImGui::Button("OK"))
		{
			resGui.destroyContext();
			resWindow.~Window();
			return 2;
		}

		ImGui::SameLine();

		if (ImGui::Button("EXIT"))
		{
			resGui.destroyContext();
			resWindow.~Window();
			return EXIT_SUCCESS;
		}

		ImGui::End();

		glClear(GL_COLOR_BUFFER_BIT);

		resGui.renderData();
		resWindow.swapBuffers();
	}

	return EXIT_SUCCESS;
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
