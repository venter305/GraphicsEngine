#include "button.h"
#include <iostream>


Button::Button(int x,int y, int w, int h, std::function<void(Button*)> action_func,Window* window,std::string vsName, std::string fsName): Panel(x,y,w,h,window,vsName,fsName){
	id = -1;
	enableMouseEvents = true;

	//Text
	text = new Text(xPos,yPos,15,"",context);
	textAlignment = TextAlignment::Center;

	action = action_func;
}

Button::~Button(){
	delete text;
}

void Button::draw(){
	Panel::draw();
	text->draw();
}

void Button::setPos(float x,float y){
	Panel::setPos(x,y);
	setTextPos();
}

void Button::setSize(float w,float h){
	Panel::setSize(w,h);
	setTextPos();
}

void Button::OnContextResize(int contextW,int contextH){
	text->OnContextResize(contextW,contextH);
	Panel::OnContextResize(contextW,contextH);
}

void Button::setText(std::string txt){
	text->setText(txt);
	setTextPos();
}

void Button::setTextSize(int size){
	text->setFontSize(size);
	setTextPos();
}

void Button::setTextColor(float r,float g, float b){
	text->setTextColor(r,g,b);
}

void Button::setTextAlignment(TextAlignment tAlign){
	textAlignment = tAlign;
	setTextPos();
}

void Button::SetTextMargins(int x,int y){
	textMarginX = x;
	textMarginY = y;
	setTextPos();
}

void Button::setTextPos(int xOffset,int yOffset){
	int textPosX = textMarginX + xOffset;
	int textPosY = yPos+(height/2)-(text->height/2)+textMarginY + yOffset;
	switch(textAlignment){
		case TextAlignment::Center:
			textPosX += xPos+(width/2)-(text->width/2);
			break;
		case TextAlignment::Left:
			textPosX += xPos;
			break;
		case TextAlignment::Right:
			break;
	}
	text->setPos(textPosX,textPosY);
}

//Change Background color
void Button::setBackgroundColor(float c1,float c2,float c3){
	setColor(c1,c2,c3,1.0f);
}

void Button::MouseEventAction(Event& ev){
	switch (ev.GetType()){
		case Event::MouseButton:
			{
				MouseButtonEvent *mEv = (MouseButtonEvent*)&ev;
				if (mEv->GetButtonType() != MouseButtonEvent::ButtonType::Left || mEv->GetButtonState() != MouseButtonEvent::ButtonState::Pressed)
					break;
				int xPos = mEv->GetMouseX();
				int yPos = mEv->GetMouseY();
				if (checkBoundingBox(xPos,yPos)){
					action(this);
				}
			}
			break;
	}
}

void Button::KeyEventAction(Event &ev){

}
