#pragma once

#include "GUIElement.h"
#include <functional>
#include "button.h"
#include "panel.h"

class MenuBar : public GUIElement{
  public:

    bool fixedAspectRatio = false;

  public:
    MenuBar(float x,float y,float width,float height,Window *context=nullptr);
    virtual ~MenuBar();

    void AddMenuButton(std::string text,std::function<void(Button*)>action_func);

    void SetBackgroundColor(float r,float g,float b,float a);
    void SetMenuButtonColor(float r,float g,float b,float a);

    void SetMenuButtonPadding(int xPadding,int yPadding);

    void SetPos(float x,float y);
    void SetSize(float w,float h);

    virtual void Draw();

    virtual void MouseEventAction(Event& ev);

    virtual void OnContextResize(int contextW,int contextH);

  private:
    Panel background;

    std::vector<Button*> menuButtons;

    float menuBtnPaddingX = 0;
    float menuBtnPaddingY = 0;

    float menuBtnColor[4] = {1.0f,1.0f,1.0f,1.0f};
};
