#pragma once

#include "Event.h"
#include "KeyEvent.h"
#include "CharEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMoveEvent.h"

class Window;
class Input{

public:

  Input();
  ~Input();

  void (*onEvent)(Event&);
  void GetMousePos(Window* window,double& x,double& y);

private:
};
