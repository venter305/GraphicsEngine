#pragma once

#include "Event.h"
#include "KeyEvent.h"
#include "CharEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMoveEvent.h"
#include "JoystickEvent.h"

class Window;
class Input{

  public:
    struct GamepadState{
      unsigned char buttons[15];
      float axis[6];
    } gamepadState;

    Input();
    ~Input();

    void OnUpdate();

    void (*onEvent)(Event&);
    void GetMousePos(Window* window,double& x,double& y);

private:
};
