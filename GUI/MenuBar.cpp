#include "MenuBar.h"

MenuBar::MenuBar(float x,float y,float w,float h,Window* window) : background(x,y,w,h){
  enableMouseEvents = true;
  xPos = x;
  yPos = y;
  width = w;
  height = h;

  if (!window)
    context = ((Window*)glfwGetWindowUserPointer(glfwGetCurrentContext()));
  else
    context = window;
}

MenuBar::~MenuBar(){
  for (int i=0;i<menuButtons.size();i++)
    delete menuButtons[i];
}

void MenuBar::AddMenuButton(std::string text,std::function<void(Button*)> action_func){
  float x = 0;
  for (int i=0;i<menuButtons.size();i++)
    x += menuButtons[i]->width + menuBtnPaddingX;
  Button *newBtn = new Button(xPos+x,yPos+menuBtnPaddingY/2.0f,10,height-menuBtnPaddingY,action_func,context);
  menuButtons.push_back(newBtn);
  newBtn->SetText(text);
  newBtn->SetSize(newBtn->text->width+10,newBtn->height);
  newBtn->SetBackgroundColor(menuBtnColor[0],menuBtnColor[1],menuBtnColor[2]);
}

void MenuBar::SetBackgroundColor(float r,float g,float b,float a){
  background.SetColor(r,g,b,a);
}

void MenuBar::SetMenuButtonColor(float r,float g,float b,float a){
  menuBtnColor[0] = r;
  menuBtnColor[1] = g;
  menuBtnColor[2] = b;
  menuBtnColor[3] = a;

  for (int i=0;i<menuButtons.size();i++)
    menuButtons[i]->SetBackgroundColor(menuBtnColor[0],menuBtnColor[1],menuBtnColor[2]);

}

void MenuBar::SetMenuButtonPadding(int xPadding,int yPadding){
  menuBtnPaddingX = xPadding;
  menuBtnPaddingY = yPadding;
}

void MenuBar::SetPos(float x,float y){
  xPos = x;
  yPos = y;
  background.SetPos(x,y);
  float btnX = x;
  for (int i=0;i<menuButtons.size();i++){
    menuButtons[i]->SetPos(btnX,yPos+menuBtnPaddingY/2.0f);
    btnX += menuButtons[i]->width + menuBtnPaddingX;
  }
}

void MenuBar::SetSize(float w,float h){
  width = w;
  height = h;
  background.SetSize(w,h);
  for (int i=0;i<menuButtons.size();i++){
    menuButtons[i]->SetSize(menuButtons[i]->width,height-menuBtnPaddingY);
  }
}

void MenuBar::Draw(){
  background.Draw();
  for (int i=0;i<menuButtons.size();i++)
    menuButtons[i]->Draw();
}

void MenuBar::MouseEventAction(Event &ev){
  for (int i=0;i<menuButtons.size();i++)
    menuButtons[i]->MouseEventAction(ev);
}

void MenuBar::OnContextResize(int contextW,int contextH){
  float aspectRatio = (float)contextW/contextH;
  if (fixedAspectRatio)
    background.OnContextResize(contextW,contextH);
  else
    background.SetSize(context->baseHeight*aspectRatio,background.height);

  for (int i=0;i<menuButtons.size();i++)
    menuButtons[i]->OnContextResize(contextW,contextH);
}
