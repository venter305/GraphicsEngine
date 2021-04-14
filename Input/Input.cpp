#include "Input.h"
#include "../Window.h"
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

  float aspectRatio = (float)width/height;

  yPos = (tmpYPos/window->height) * window->baseHeight;
  xPos = (tmpXPos/window->width) * window->baseHeight * aspectRatio;

  std::cout << "\r                              \r" << xPos << ' ' << yPos <<  std::flush;


}
