#pragma once

#include <iostream>
#include "Input/Input.h"
#include "GUI/GUIManager.h"

class Window {
  public:
    int width = 0;
    int height = 0;

    float baseWidth = 0;
    float baseHeight = 0;

    std::string title = "New Window";

    Window(int w,int h,std::string name):width(w),height(h),title(name),baseWidth(w),baseHeight(h){
    };

    void Init(int w,int h,std::string name){
      width = w;
      height = h;
      baseWidth = w;
      baseHeight = h;
      title = name;
    }

    virtual ~Window(){
      glfwDestroyWindow(window);
    }

    virtual void SetSize(int w,int h){
      width = w;
      height = h;
      guiMan.Resize(w,h);
    }

    virtual void OnStartup() = 0;
    virtual void OnUpdate(double dTime) = 0;
    virtual void OnShutdown() = 0;

    virtual void OnEvent(Event &ev) = 0;

    GLFWwindow* GetGLFWwindow(){return window;};

  protected:
    GLFWwindow *window = nullptr;
    GUIManager guiMan;

    friend class GraphicsEngine;

};
