#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "GUI/Window.h"
#include "Utility/Utility.h"
#include "Utility/TrackAllocation.h"
#include "Utility/Timer.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"
#include "GUI/GUI.h"
#include "Scene/Scene.h"
#include "GUI/SettingsWindow.h"

int main()
{
	// Settings m_window
	SettingsWindow resWindow{ "Resolution settings" };

	int const code = resWindow.run();

	if (code == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (code == EXIT_SUCCESS)
		return EXIT_SUCCESS;

	// App Window
	Window mainWindow("Computational Geometry 2020/2021, Manuel Pagliuca, Matricola : 975169", resWindow.getFullscreenMode(), resWindow.pickedResolution());

	if (!mainWindow.initialise())
	{
		std::cerr << "Error initialising the application window.\n";
		mainWindow.~Window();
		return EXIT_FAILURE;
	}

	GUI gui{ mainWindow.getAspectRatio(), mainWindow.getWidth(), mainWindow.getHeight() };
	gui.setupContext(mainWindow.getWindowObject());

	Scene scene = Scene(mainWindow.getProjectionMatrix());
	scene.loadSceneObjects();
	scene.loadSceneShaders();

	while (!mainWindow.getShouldClose())
	{
		glfwPollEvents();
		glClearColor(0.f, 0.f, 0.f, 1.f);

		/* update the glfwindow */
		mainWindow.update();

		/* init gui */
		gui.initFrame();

		ImGui::ShowDemoWindow();

		/* gui panels */
		gui.objectsPanel();
		gui.tessPanel();
		gui.shaderPanel();
		gui.menuBar();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* render scene */
		scene.renderScene(
			static_cast<float>(mainWindow.getDeltaTime()),
			gui.getObjectGUIParams(),
			gui.getTessellationGUIParams());

		/* render gui */
		gui.renderData();

		/* unbind shader */
		glUseProgram(0);

		/* swap front and back buffer */
		mainWindow.swapBuffers();
	}

	gui.destroyContext();

	return 1;
}
