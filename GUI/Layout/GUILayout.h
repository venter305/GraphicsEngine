#pragma once
#include <vector>
#include <memory>
#include "../GUIElement.h"

class GUILayout : public GUIElement {
  public:

  protected:
    std::vector<std::shared_ptr<GUIElement>> elements;

  public:
    template<typename T>
    std::shared_ptr<GUIElement> GetElement(int index){return std::static_pointer_cast<T>(elements[id]);}
    std::vector<std::shared_ptr<GUIElement>>* GetElementList(){return &elements;}
    int NumberOfElements(){return elements.size();}

    virtual ~GUILayout() = default;

  protected:
    GUILayout(float x,float y){
      xPos = x;
      yPos = y;
      enableMouseEvents = true;
      enableKeyEvents = true;
    }

};
