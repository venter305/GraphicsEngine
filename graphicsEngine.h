#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "Input/Input.h"
#include "GUI/GUIManager.h"
#include "GUI/panel.h"
#include "GUI/textObject.h"
#include "GUI/button.h"
#include "GUI/textInput.h"

class GraphicsEngine{
private:
	static int width;
	static int height;
	static GLFWwindow *window;
	static std::string title;

public:

	static Input input;
	static GUIManager guiMan;

	static void Init(int,int,std::string,void(*)(GLFWwindow*,double));
	static void Run();

private:
	static void (*mainLoop)(GLFWwindow*,double);

};
