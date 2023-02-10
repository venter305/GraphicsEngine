#pragma once

#include "Event.h"

class MouseScrollEvent : public Event {

	public:
		MouseScrollEvent(double offset):scrollOffset(offset){type = Event::EventType::MouseScroll;};
		
		double GetScrollOffset() const {return scrollOffset;}
	private:
		double scrollOffset = 0;	
};
