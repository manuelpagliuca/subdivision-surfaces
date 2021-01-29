#pragma once

#include "Window.h"
#include "GUI.h"

class SettingsWindow
{
public:
	SettingsWindow() = default;
	~SettingsWindow() = default;

	int run();

private:
	Window window{ "Resolution settings", 400, 100 };
};