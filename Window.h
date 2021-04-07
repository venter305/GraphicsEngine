#pragma once

#include <iostream>
#include "Input/Input.h"
#include "GUI/GUIManager.h"

class Window {
  public:
    int width = 0;
    int height = 0;

    std::string title = "New Window";

    Window(int w,int h,std::string name):width(w),height(h),title(name){};

    void Init(int w,int h,std::string name){
      width = w;
      height = h;
      title = name;
    }

    virtual ~Window(){
      glfwDestroyWindow(window);
    }

    virtual void OnStartup() = 0;
    virtual void OnUpdate(double dTime) = 0;
    virtual void OnShutdown() = 0;

    virtual void OnEvent(Event &ev) = 0;

  protected:
    GLFWwindow *window = nullptr;
    GUIManager guiMan;

    friend class GraphicsEngine;

};
