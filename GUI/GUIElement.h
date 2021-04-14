#pragma once

#include "../Input/Input.h"
#include "../Window.h"

class GUIElement{
public:
  bool enableMouseEvents = false;
  bool enableKeyEvents = false;

  virtual void draw() = 0;

  void SetId(int _id){id = _id;}
  virtual void MouseEventAction(Event& ev){};
  virtual void KeyEventAction(Event& ev){};

  virtual void OnContextResize(int width,int height){};

  Window* GetContext() {return context;};

protected:
  Window* context = nullptr;
  int id;
};
