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

	glfwSetKeyCallback(window,[](GLFWwindow* win, int key, int scancode, int action, int mods){
		glfwMakeContextCurrent(win);
		KeyEvent ev(key,(KeyEvent::KeyState)action);
		((Window*)glfwGetWindowUserPointer(win))->OnEvent(ev);
	});

	glfwSetCharCallback(window,[](GLFWwindow* win,unsigned int keycode){
		glfwMakeContextCurrent(win);
		CharEvent ev(keycode);
		((Window*)glfwGetWindowUserPointer(win))->OnEvent(ev);
	});

	glfwSetMouseButtonCallback(window,[](GLFWwindow* win, int button, int action, int mods){
		glfwMakeContextCurrent(win);
		double mouseX,mouseY;
		input.GetMousePos(((Window*)glfwGetWindowUserPointer(win)),mouseX,mouseY);
		MouseButtonEvent ev((MouseButtonEvent::ButtonType)button,(MouseButtonEvent::ButtonState)action,mouseX,mouseY);
		((Window*)glfwGetWindowUserPointer(win))->OnEvent(ev);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xPos,double yPos){
		glfwMakeContextCurrent(win);
		MouseMoveEvent ev(xPos,yPos);
		((Window*)glfwGetWindowUserPointer(win))->OnEvent(ev);
	});

	glfwSetWindowSizeCallback(window,[](GLFWwindow* win,int width,int height){
		glfwMakeContextCurrent(win);
		((Window*)glfwGetWindowUserPointer(win))->SetSize(width,height);

		int w,h;
		glfwGetFramebufferSize(win,&w,&h);
		glViewport(0,0,w,h);

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
	int frames = 0;

	for (auto window : windows){
		glfwMakeContextCurrent(window->window);
		window->OnStartup();
	}

	while(!windows.empty()){
		frames++;
		glfwPollEvents();
		for (auto it = windows.begin(); it != windows.end(); it++){
			auto window = *it;
			//mainLoop(window,glfwGetTime());
			glfwMakeContextCurrent(window->window);
			window->OnUpdate(glfwGetTime());
			if (glfwGetTime()-dTime >= 1)
				glfwSetWindowTitle(window->GetGLFWwindow(),(window->title + " - Program FPS:" + std::to_string(frames)).c_str());
			glfwSwapBuffers(window->window);
			if (glfwWindowShouldClose(window->window)){
				window->OnShutdown();
				delete window;
				windows.erase(it--);
			}
		}

		if (glfwGetTime()-dTime >= 1){
			frames = 0;
			dTime = glfwGetTime();
		}
	}
}
