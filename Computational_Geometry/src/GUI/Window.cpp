#include "Window.h"

Window::Window(const char* t_windowTitle, const int t_windowWidth, const int t_windowHeight, const bool t_fullscreen)
{
	m_windowTitle = t_windowTitle;
	m_width = t_windowWidth;
	m_height = t_windowHeight;
	m_fullscreen = t_fullscreen;
}

Window::Window(const char* t_windowTitle, const bool t_fullscreen, ResolutionType const& res)
{
	m_windowTitle = t_windowTitle;
	m_fullscreen = t_fullscreen;

	switch (res)
	{
	case ResolutionType::RES_1920_1080:
		m_width = 1920;
		m_height = 1080;
		break;
	case ResolutionType::RES_1240_720:
		m_width = 1240;
		m_height = 720;
		break;
	case ResolutionType::RES_800_600:
		m_width = 800;
		m_height = 600;
		break;
	case ResolutionType::RES_1280_1024:
		m_width = 1280;
		m_height = 1024;
		break;
	default:
		m_width = 1240;
		m_height = 720;
		break;
	}

}

Window::Window(const char* t_windowTitle, const bool t_fullscreenMode)
{
	m_windowTitle = t_windowTitle;
	m_fullscreen = t_fullscreenMode;
	m_width = 1920;
	m_height = 1080;
}

/* member functions */
int Window::initialise()
{
	if (!glfwInit())
	{
		perror("Error initialising GLFW.\n");
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (m_fullscreen) {
		m_window = glfwCreateWindow(m_width, m_height, m_windowTitle, glfwGetPrimaryMonitor(), nullptr);
	}
	else {
		m_window = glfwCreateWindow(m_width, m_height, m_windowTitle, nullptr, nullptr);
	}

	if (m_window == nullptr)
	{
		perror("Error initialising the window.\n");
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -1;
	}

	glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);

	m_primaryMonitor = glfwGetPrimaryMonitor();

	glfwMakeContextCurrent(m_window);

	createCallBacks();

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewExperimental = GL_TRUE;

	const GLFWvidmode* mode = glfwGetVideoMode(m_primaryMonitor);

	glfwGetMonitorPos(m_primaryMonitor, &m_monitorX, &m_monitorY);
	glfwSetWindowPos(m_window, m_monitorX + (mode->width - m_width) / 2, m_monitorY + (mode->height - m_height) / 2);

	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		std::cout << "Error initialising GLEW : " << glewGetErrorString(error) << "\n";
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);

	glViewport(0, 0, m_bufferWidth, m_bufferHeight);

	glfwSetWindowUserPointer(m_window, this);	// La funzione e' statica non sa a quale oggetto riferirsi, la m_window in entrata su handle_keys ora sapr� che si riferisce a a quest'oggetto

	return 1;
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_window);
}

void Window::update()
{
	/* FPS & m_deltaTime */
	const double max_fps = 60.;
	const double max_period = 1. / max_fps;

	double now = glfwGetTime();
	m_deltaTime = now - m_lastTime;

	if (m_deltaTime >= max_period)
	{
		m_lastTime = now;
		char title[256];
		sprintf(title, "Computational Geometry 2020/2021, Manuel Pagliuca [%.2f FPS]", 1.f / m_deltaTime);
		glfwSetWindowTitle(m_window, title);
	}

	/* Adjust frame on resize */
	GLint newBufferWidth, newBufferHeight;

	glfwGetFramebufferSize(m_window, &newBufferWidth, &newBufferHeight);

	if (newBufferWidth != m_bufferWidth || newBufferHeight != m_bufferHeight)
	{
		m_bufferWidth = newBufferWidth;
		m_bufferHeight = newBufferHeight;

		glViewport(0, 0, m_bufferWidth, m_bufferHeight);
		glScissor(0, 0, m_bufferWidth, m_bufferHeight);
		glEnable(GL_SCISSOR_TEST);
	}

	/* Mouse coordinates */
	glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
}

void Window::createCallBacks()
{
	glfwSetKeyCallback(m_window, handleKeys);
	glfwSetCursorPosCallback(m_window, handleMouse);
}

void Window::handleKeys(GLFWwindow* t_window, int t_key, int t_code, int t_action, int t_mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(t_window));

	if (t_key == GLFW_KEY_ESCAPE && t_action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(t_window, GL_TRUE);
	}

	if (t_key >= 0 && t_key < 1024)
	{
		if (t_action == GLFW_PRESS)
		{
			theWindow->m_keys[t_key] = true;
		}
		else if (t_action == GLFW_RELEASE)
		{
			theWindow->m_keys[t_key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* t_window, double t_xPos, double  t_yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(t_window));

	if (theWindow->m_mouseFirstMoved)
	{
		theWindow->m_lastX = static_cast<GLfloat>(t_xPos);
		theWindow->m_lastY = static_cast<GLfloat>(t_yPos);
		theWindow->m_mouseFirstMoved = false;
	}

	theWindow->m_xChange = (static_cast<GLfloat>(t_xPos) - theWindow->m_lastX);
	theWindow->m_yChange = theWindow->m_lastY - (static_cast<GLfloat>(t_yPos));

	theWindow->m_lastX = static_cast<GLfloat>(t_xPos);
	theWindow->m_lastY = static_cast<GLfloat>(t_yPos);
}

/* getters */
float Window::getXChange()
{
	GLfloat theChange = m_xChange;
	m_xChange = 0.0f;
	return theChange;
}

const double Window::getMouseX() const
{
	return m_mouseX;
}

const double Window::getMouseY() const
{
	return m_mouseY;
}

float Window::getYChange()
{
	GLfloat theChange = m_yChange;
	m_yChange = 0.0f;
	return theChange;
}

const int Window::getBufferWidth() const
{
	return m_bufferWidth;
}

const int Window::getBufferHeight() const
{
	return m_bufferHeight;
}

const int Window::getHeight() const
{
	return m_height;
}

const int Window::getWidth() const
{
	return m_width;
}

float Window::getAspectRatio() const
{
	return static_cast<float>(m_bufferWidth) / static_cast<float>(m_bufferHeight);
}

glm::mat4 Window::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(45.f), getAspectRatio(), 0.1f, 100.f);
}

GLFWwindow* Window::getWindowObject()
{
	return m_window;
}

bool* Window::getKeys()
{
	return m_keys;
}

bool Window::getShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

double Window::getDeltaTime()
{
	return m_deltaTime;
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}