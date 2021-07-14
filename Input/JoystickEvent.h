#pragma once

#include "Event.h"

class JoystickButtonEvent : public Event {
  public:
    enum ButtonState{
      None = -1,
      Released = 0,
      Pressed = 1
    };

    JoystickButtonEvent(uint8_t btn,ButtonState bState) : button(btn), state(bState){
      type = EventType::JoystickButton;
    }

    uint8_t GetButton(){return button;}
    ButtonState GetState(){return state;}

  private:
    uint8_t button = -1;
    ButtonState state = ButtonState::None;
};
