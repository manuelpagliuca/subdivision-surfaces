#include "SettingsWindow.h"

int SettingsWindow::run()
{
	if (!window.initialise())
	{
		std::cerr << "Error initialising the boot window.\n";
		window.~Window();
		return EXIT_FAILURE;
	}

	GUI resGui{};
	resGui.setupContext(window.getWindowObject());

	while (!window.getShouldClose())
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
			window.~Window();
			return 2;
		}

		ImGui::SameLine();

		if (ImGui::Button("EXIT"))
		{
			resGui.destroyContext();
			window.~Window();
			return EXIT_SUCCESS;
		}

		ImGui::End();

		glClear(GL_COLOR_BUFFER_BIT);

		resGui.renderData();
		window.swapBuffers();
	}

	return EXIT_SUCCESS;
}