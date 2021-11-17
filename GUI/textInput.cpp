#include "textInput.h"
#include <iostream>

using namespace std;


TextInput::TextInput(int x,int y,int w,int h,string t,std::function<void(TextInput*)> action_func,Window* window,string vsName,string fsName): Button(x,y,w,h,NULL,window,vsName,fsName){
	//Init
	//text = new Text(0,0,15,t,"/usr/share/fonts/TTF/DejaVuSerif.ttf");

	enableMouseEvents = true;
	enableKeyEvents = true;

	DisableAction = action_func;
	SetEnabled(false);
	//drawText();

	SetText(t);


	prevInTime = 0;
	inputTimer = 0;
	inTimeMax = 0.12;
	inputMask = "abcdefghijklmnopqrstuvwxyz.0123456789/";
}

void TextInput::AddCharacter(char newChar){
	SetText(text->text+newChar);
}

void TextInput::RemoveCharacter(){
	if (text->text.empty())
		return;
	text->text.pop_back();
	SetText(text->text);
}

void TextInput::SetEnabled(bool state){
	if (state){
		SetBackgroundColor(enabledColor[0],enabledColor[1],enabledColor[2]);
	}
	else{
		SetBackgroundColor(disabledColor[0],disabledColor[1],disabledColor[2]);
		if (enabled && DisableAction != nullptr) DisableAction(this);
	}

	enabled = state;
}

void TextInput::SetEnabledColor(float color[3]){
	enabledColor[0] = color[0];
	enabledColor[1] = color[1];
	enabledColor[2] = color[2];
	SetEnabled(enabled);
}

void TextInput::SetDisabledColor(float color[3]){
	disabledColor[0] = color[0];
	disabledColor[1] = color[1];
	disabledColor[2] = color[2];
	SetEnabled(enabled);
}

void TextInput::SetStateColors(float eColor[3], float dColor[3]){
	SetEnabledColor(eColor);
	SetDisabledColor(dColor);
}

void TextInput::MouseEventAction(Event &ev){
	switch(ev.GetType()){
		case Event::MouseButton:
			{
				MouseButtonEvent *mEv = (MouseButtonEvent*)&ev;
				if (mEv->GetButtonType() != MouseButtonEvent::ButtonType::Left || mEv->GetButtonState() != MouseButtonEvent::ButtonState::Pressed)
					break;
				SetEnabled(CheckBoundingBox(mEv->GetMouseX(),mEv->GetMouseY()));
			}
			break;
		case Event::MouseCursor:
			{
				MouseMoveEvent *mEv = (MouseMoveEvent*)&ev;
				int xPos = mEv->GetMouseX();
				int yPos = mEv->GetMouseY();
				if (CheckBoundingBox(xPos,yPos)){
					if (hovered)
						SetColor(hoverColor);
					hovered = true;
				}
				else if(hovered){
					SetColor(backgroundColor);
					hovered = false;
				}
			}
			break;
	}
}

void TextInput::KeyEventAction(Event &ev){
	switch(ev.GetType()){
		case Event::Key:
			{
				int keyCode = static_cast<KeyEvent*>(&ev)->GetKeyCode();
				int keyState = static_cast<KeyEvent*>(&ev)->GetKeyState();
				if (keyState == KeyEvent::KeyState::Released)
					break;

				if(!enabled)
					break;
				if (keyCode == GLFW_KEY_BACKSPACE)
					RemoveCharacter();
				else if (keyCode == GLFW_KEY_ENTER)
					SetEnabled(false);
			}
			break;
		case Event::Character:
			{
				unsigned int charCode = static_cast<CharEvent*>(&ev)->GetCharCode();
				if (enabled)
					AddCharacter(charCode);
			}
			break;
	}
}
