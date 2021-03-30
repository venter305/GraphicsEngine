#pragma once

//test

class GUIElement{
public:
  virtual void draw() = 0;

  void SetId(int _id){id = _id;}
  virtual void clickAction(int mouseX,int mouseY){};

protected:
  int id;
};
