#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "Input/Input.h"
#include "Window.h"

#include "GUI/panel.h"
#include "GUI/textObject.h"
#include "GUI/button.h"
#include "GUI/textInput.h"
#include "GUI/MenuBar.h"
#include "GUI/Checkbox.h"

#include "GUI/Layout/ListLayout.h"
#include "GUI/Layout/GridLayout.h"

class GraphicsEngine{
private:
	static int width;
	static int height;
	static std::vector<Window*> windows;

public:

	static Input input;
	static Window *focusedWindow;

	static void AddWindow(Window* window);
	static void CloseAllWindows();
	static void Init();
	static void Run();

private:
	static void (*mainLoop)(GLFWwindow*,double);

};
