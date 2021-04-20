#pragma once

#include "GraphicsEngine/Window.h"

class ElementTestWindow : public Window{
	public:

		ElementTestWindow(int w,int h,std::string name):Window(w,h,name){
		}

		void OnStartup(){
			glClearColor(0.9f,0.9f,0.9f,1.0f);
		}

		void OnUpdate(double dTime){
			glClear(GL_COLOR_BUFFER_BIT);
			guiMan.drawElements();

		}

		void OnShutdown(){
		}

		void OnEvent(Event &ev){
			guiMan.HandleEvent(ev);
		}

};
