#include "GUIManager.h"
#include "GUIElement.h"
#include <iostream>

GUIManager::GUIManager(){

}

void GUIManager::drawElements(){
	std::map<int,std::shared_ptr<GUIElement>>::iterator it;
	for (it = elements.begin();it != elements.end();it++){
		it->second->draw();
	}
}

int GUIManager::addElement(std::shared_ptr<GUIElement> element,int id){
	if (id == -1)
		id = elements.size();
	element->SetId(id);
	elements.insert({id,element});
	return id;
}

void GUIManager::HandleEvent(Event& ev){
	for (auto element : elements){
		if (element.second->enableMouseEvents && ev.GetType()&(Event::MouseCursor|Event::MouseButton)){
			element.second->MouseEventAction(ev);
		}
		if (element.second->enableKeyEvents && ev.GetType()&(Event::Key|Event::Character))
			element.second->KeyEventAction(ev);
	}
}
