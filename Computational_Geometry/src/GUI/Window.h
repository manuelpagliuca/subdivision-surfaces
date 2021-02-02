#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning(push, 0)
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#pragma warning(pop)

enum class ResolutionType {
	RES_1920_1080,
	RES_1280_1024,
	RES_1240_720,
	RES_800_600
};

class Window
{
public:
	Window() = default;
	Window(const char* t_windowTitle, const int t_windowWidth, const int t_windowHeight, const bool t_fullscreen = false);
	Window(char const* t_windowTitle, bool const t_fullscreen, ResolutionType const& res);
	Window(const char* t_windowTitle, const bool t_fullscreenMode = false);
	~Window();

	/* member function */
	int initialise();
	void swapBuffers() const;
	void update();

	/* getters */
	const int getBufferWidth() const;
	const int getBufferHeight() const;
	const int getWidth() const;
	const int getHeight() const;

	float getAspectRatio() const;
	glm::mat4 getProjectionMatrix()const;
	GLFWwindow* getWindowObject();
	bool* getKeys();
	GLfloat getXChange();
	GLfloat getYChange();
	const double getMouseX() const;
	const double getMouseY() const;
	bool getShouldClose() const;
	double getDeltaTime();

private:
	/* private functions */
	void createCallBacks();

	/* static functions */
	static void handleKeys(GLFWwindow* t_window, int t_key, int t_code, int t_action, int t_mode);
	static void handleMouse(GLFWwindow* t_window, double t_xPos, double t_yPos);

	/* the m_window object */
	GLFWwindow* m_window{ nullptr };
	GLFWmonitor* m_primaryMonitor{ nullptr };

	/* aspect ratio */
	GLint m_width{ 800 };
	GLint m_height{ 600 };
	GLint m_bufferWidth{};
	GLint m_bufferHeight{};
	bool m_fullscreen{ false };
	const char* m_windowTitle{ nullptr };

	/* centering the m_window */
	int m_monitorX{};
	int m_monitorY{};

	/* handle keyboard input*/
	bool* m_keys = new bool[1024]{ false };

	/* handle mouse input */
	GLfloat m_lastX{};
	GLfloat m_lastY{};
	GLfloat m_xChange{};
	GLfloat m_yChange{};
	double m_mouseX{};
	double m_mouseY{};

	bool m_mouseFirstMoved{ true };

	/* fps */
	double m_deltaTime{};
	double m_lastTime{};
};