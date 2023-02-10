#include "MouseMoveEvent.h"
#include <cstdio>

MouseMoveEvent::MouseMoveEvent(double mouseX,double mouseY) : mosPosX(mouseX),mosPosY(mouseY){
  type = EventType::MouseCursor;
  
}

MouseMoveEvent::~MouseMoveEvent(){

}
