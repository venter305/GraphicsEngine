#include "Input.h"
#include "../Window.h"
#include <GLFW/glfw3.h>
Input::Input(){

}

Input::~Input(){

}

void Input::GetMousePos(Window *window,double &xPos, double &yPos){
  GLFWwindow *glfwWindow =  window->GetGLFWwindow();

  double tmpYPos,tmpXPos;
  glfwGetCursorPos(glfwWindow,&tmpXPos,&tmpYPos);

  tmpYPos = tmpYPos-window->height;
  if (tmpYPos < 0) tmpYPos *= -1;

  float aspectRatio = (float)window->width/window->height;

  yPos = (tmpYPos/window->height) * window->baseHeight;
  xPos = (tmpXPos/window->width) * window->baseHeight * aspectRatio;
}
