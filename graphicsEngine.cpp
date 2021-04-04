#include "graphicsEngine.h"
#include <iostream>

Input GraphicsEngine::input;
//GUIManager GraphicsEngine::guiMan;

int GraphicsEngine::width;
int GraphicsEngine::height;
std::vector<Window*> GraphicsEngine::windows;

void (*GraphicsEngine::mainLoop)(GLFWwindow*,double);

void GraphicsEngine::Init(){
	if (!glfwInit()){
		return;
	}

}

void GraphicsEngine::AddWindow(Window* newWindow){
	GLFWwindow *window = glfwCreateWindow(newWindow->width,newWindow->height,newWindow->title.c_str(),NULL, NULL);
	newWindow->window = window;
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window,newWindow);

	glfwSetKeyCallback(window,[](GLFWwindow* window, int key, int scancode, int action, int mods){
		glfwMakeContextCurrent(window);
		KeyEvent ev(key,(KeyEvent::KeyState)action);
		((Window*)glfwGetWindowUserPointer(window))->OnEvent(ev);
	});

	glfwSetCharCallback(window,[](GLFWwindow* window,unsigned int keycode){
		glfwMakeContextCurrent(window);
		CharEvent ev(keycode);
		((Window*)glfwGetWindowUserPointer(window))->OnEvent(ev);
	});

	glfwSetMouseButtonCallback(window,[](GLFWwindow* window, int button, int action, int mods){
		glfwMakeContextCurrent(window);
		double mouseX,mouseY;
		input.GetMousePos(window,mouseX,mouseY);
		MouseButtonEvent ev((MouseButtonEvent::ButtonType)button,(MouseButtonEvent::ButtonState)action,mouseX,mouseY);
		((Window*)glfwGetWindowUserPointer(window))->OnEvent(ev);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos,double yPos){
		glfwMakeContextCurrent(window);
		MouseMoveEvent ev(xPos,yPos);
		((Window*)glfwGetWindowUserPointer(window))->OnEvent(ev);
	});


	//Enable transparent textures
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glewInit();

	windows.push_back(newWindow);
}

void GraphicsEngine::Run(){
	//float startTime = glfwGetTime();
	float dTime = 0;
	int y = 0;

	for (auto window : windows){
		glfwMakeContextCurrent(window->window);
		window->OnStartup();
	}

	while(!windows.empty()){
		y++;
		glfwPollEvents();
		for (auto it = windows.begin(); it != windows.end(); it++){
			auto window = *it;
			//mainLoop(window,glfwGetTime());
			glfwMakeContextCurrent(window->window);
			window->OnUpdate(glfwGetTime());
			//std::string title = window.name;
			// if (glfwGetTime()-dTime >= 1){
			// 	glfwSetWindowTitle(window,(title + " - Program FPS:" + std::to_string(y)).c_str());
			// 	y = 0;
			// 	dTime = glfwGetTime();
			// }
			glfwSwapBuffers(window->window);
			if (glfwWindowShouldClose(window->window)){
				window->OnShutdown();
				delete window;
				windows.erase(it--);
			}
		}
	}
}
