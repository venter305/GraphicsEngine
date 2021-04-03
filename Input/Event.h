#pragma once

class Event{

public:
  enum EventType{
    None = 0,
    Key = 1,
    Character = 1<<1,
    MouseCursor = 1<<2,
    MouseButton = 1<<3,
    Window = 1<<4
  };

  Event();
  ~Event();

  EventType GetType() {return type;};

protected:
  EventType type = EventType::None;


};
