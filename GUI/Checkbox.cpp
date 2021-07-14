#include "Checkbox.h"

Checkbox::Checkbox(int x,int y,int w,int h,bool *valPtr) : val(valPtr),Button(x,y,w,h,nullptr){

}

void Checkbox::MouseEventAction(Event& ev){
	switch (ev.GetType()){
		case Event::MouseButton:
			{
				MouseButtonEvent *mEv = (MouseButtonEvent*)&ev;
				if (mEv->GetButtonType() != MouseButtonEvent::ButtonType::Left || mEv->GetButtonState() != MouseButtonEvent::ButtonState::Pressed)
					break;
				int xPos = mEv->GetMouseX();
				int yPos = mEv->GetMouseY();
				if (checkBoundingBox(xPos,yPos)){
          if (*val){
            *val = false;
            setText("");
          }
          else{
            *val = true;
            setText("X");
          }
				}
			}
			break;
	}
}

void Checkbox::SetChecked(bool value){
  if (!value){
    *val = false;
    setText("");
  }
  else{
    *val = true;
    setText("X");
  }
}
