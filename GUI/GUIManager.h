#pragma once

#include <map>
#include <memory>
#include "GUIElement.h"

class GUIManager{
	public:
		std::map<int,std::shared_ptr<GUIElement>> elements;

		GUIManager();
		void drawElements();
		int addElement(std::shared_ptr<GUIElement>,int=-1);
		void HandleEvent(Event& ev);

		template<typename T>
		std::shared_ptr<T> GetElement(int id){return std::static_pointer_cast<T>(elements[id]);};

};
