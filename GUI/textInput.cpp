#include "textInput.h"
#include <iostream>

using namespace std;


TextInput::TextInput(int x,int y,int w,int h,string t,void(*action_func)(TextInput*),Window* window,string vsName,string fsName): Button(x,y,w,h,NULL,window,vsName,fsName){
	//Init
	//text = new Text(0,0,15,t,"/usr/share/fonts/TTF/DejaVuSerif.ttf");

	enableMouseEvents = true;
	enableKeyEvents = true;

	disableAction = action_func;
	setEnabled(false);
	//drawText();

	setText(t);


	prevInTime = 0;
	inputTimer = 0;
	inTimeMax = 0.12;
	inputMask = "abcdefghijklmnopqrstuvwxyz.0123456789/";
}

void TextInput::addCharacter(char newChar){
	setText(text->text+newChar);
}

void TextInput::removeCharacter(){
	if (text->text.empty())
		return;
	text->text.pop_back();
	setText(text->text);
}

void TextInput::setEnabled(bool state){
	if (state){
		setBackgroundColor(enabledColor[0],enabledColor[1],enabledColor[2]);
	}
	else{
		setBackgroundColor(disabledColor[0],disabledColor[1],disabledColor[2]);
		if (enabled && disableAction != nullptr) disableAction(this);
	}

	enabled = state;
}

void TextInput::setEnabledColor(float color[3]){
	enabledColor[0] = color[0];
	enabledColor[1] = color[1];
	enabledColor[2] = color[2];
	setEnabled(enabled);
}

void TextInput::setDisabledColor(float color[3]){
	disabledColor[0] = color[0];
	disabledColor[1] = color[1];
	disabledColor[2] = color[2];
	setEnabled(enabled);
}

void TextInput::setStateColors(float eColor[3], float dColor[3]){
	setEnabledColor(eColor);
	setDisabledColor(dColor);
}

void TextInput::MouseEventAction(Event &ev){
	switch(ev.GetType()){
		case Event::MouseButton:
			{
				MouseButtonEvent *mEv = (MouseButtonEvent*)&ev;
				if (mEv->GetButtonType() != MouseButtonEvent::ButtonType::Left || mEv->GetButtonState() != MouseButtonEvent::ButtonState::Pressed)
					break;
				setEnabled(checkBoundingBox(mEv->GetMouseX(),mEv->GetMouseY()));
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
					removeCharacter();
				else if (keyCode == GLFW_KEY_ENTER)
					setEnabled(false);
			}
			break;
		case Event::Character:
			{
				unsigned int charCode = static_cast<CharEvent*>(&ev)->GetCharCode();
				if (enabled)
					addCharacter(charCode);
			}
			break;
	}
}
