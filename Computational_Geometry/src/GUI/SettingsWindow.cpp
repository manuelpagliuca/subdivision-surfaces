#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(const char* windowTitle)
{
	m_window = Window(windowTitle, 300, 120, false);
}

int SettingsWindow::run()
{
	if (!m_window.initialise())
	{
		std::cerr << "Error initialising the boot window.\n";
		m_window.~Window();
		return EXIT_FAILURE;
	}

	GUI resGui{};
	resGui.setupContext(m_window.getWindowObject());

	while (!m_window.getShouldClose())
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

		ImGui::SetNextWindowSize(ImVec2(300.f, 120.f));
		ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_FirstUseEver);

		ImGui::Begin("Settings", nullptr, window_flags);

		ImGui::SameLine(50);
		ImGui::Text("Select your screen resolution: ");
		ImGui::NewLine();
		ImGui::SameLine(50);

		ImGui::Combo("", &m_res, "1920x1080\0" "1280x1024\0" "1240x720\0" "800x600\0");

		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::SameLine(50);
		ImGui::Checkbox("Cache", resGui.getCache());
		ImGui::SameLine();
		ImGui::Checkbox("Fullscreen", &fullscreenMode);
		ImGui::NewLine();
		ImGui::SameLine(210);

		if (ImGui::Button("OK"))
		{
			resGui.destroyContext();
			m_window.~Window();
			return 2;
		}

		ImGui::SameLine();

		if (ImGui::Button("EXIT"))
		{
			resGui.destroyContext();
			m_window.~Window();
			return EXIT_SUCCESS;
		}

		ImGui::End();

		glClear(GL_COLOR_BUFFER_BIT);

		resGui.renderData();
		m_window.swapBuffers();
	}

	return EXIT_SUCCESS;
}
