#pragma once

#include "Window.h"
#include "GUI.h"

class SettingsWindow
{
public:
	SettingsWindow(const char* windowTitle);
	~SettingsWindow() = default;

	int run();

	ResolutionType pickedResolution() const {
		switch (m_res)
		{
		case 0:
		default:
			return ResolutionType::RES_1920_1080;
			break;
		case 1:
			return ResolutionType::RES_1280_1024;
			break;
		case 2:
			return ResolutionType::RES_1240_720;
			break;
		case 3:
			return ResolutionType::RES_800_600;
			break;
		}
	}

	bool getFullscreenMode() const { return fullscreenMode; }

private:
	Window m_window{};
	int m_res{ 0 };
	bool fullscreenMode{ false };
};