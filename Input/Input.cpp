#include <iostream>

#include "../graphicsEngine.h"
#include "Input.h"
#include "../Window.h"
#include <GLFW/glfw3.h>

Input::Input(){
  for (int i=0;i<15;i++)
    gamepadState.buttons[i] = 0;
  for (int i=0;i<6;i++)
    gamepadState.axis[i] = 0;
}

Input::~Input(){

}

void Input::OnUpdate(){
  //Joystick
  if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)){
    Window *currWindow = GraphicsEngine::focusedWindow;
    GLFWgamepadstate newState;
    if (glfwGetGamepadState(GLFW_JOYSTICK_1,&newState)){
        for (int i=0;i<15;i++){
          if (newState.buttons[i] != gamepadState.buttons[i]){
            gamepadState.buttons[i] = newState.buttons[i];
            JoystickButtonEvent ev(i,(JoystickButtonEvent::ButtonState)gamepadState.buttons[i]);
            currWindow->OnEvent(ev);
          }

        }
    }
  }
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

int Input::GetKeyState(GLFWwindow *context, int key){
  return glfwGetKey(context,key);
}
