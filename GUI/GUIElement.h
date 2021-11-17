#pragma once

#include "../Window.h"

class GUIElement{
public:
  bool enableMouseEvents = false;
  bool enableKeyEvents = false;

  float xPos = 0;
  float yPos = 0;
  float width = 0;
  float height = 0;

  bool visable = true;

  bool hovered = false;

  virtual void Draw(){};

  virtual void SetPos(float x,float y){
    xPos = x;
    yPos = y;
  }

  virtual void SetSize(float w,float h){
    width = w;
    height = h;
  }

  void SetId(int _id){id = _id;}
  int GetId(){return id;}
  virtual void MouseEventAction(Event& ev){};
  virtual void KeyEventAction(Event& ev){};

  virtual void OnContextResize(int width,int height){};

  Window* GetContext() {return context;};

protected:
  Window* context = nullptr;
  int id;
};
