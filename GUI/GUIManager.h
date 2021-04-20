#pragma once

#include <map>
#include <memory>
#include "../Input/Event.h"

class GUIElement;
class GUILayout;
class GUIManager{

	public:
		std::map<int,std::shared_ptr<GUIElement>> elements;

		GUIManager();
		void drawElements();
		int addElement(std::shared_ptr<GUIElement>,int=-1);
		void AddLayout(std::shared_ptr<GUILayout>);
		void HandleEvent(Event& ev);
		void Resize(int width,int height);

		template<typename T>
		std::shared_ptr<T> GetElement(int id){return std::static_pointer_cast<T>(elements[id]);};

};
