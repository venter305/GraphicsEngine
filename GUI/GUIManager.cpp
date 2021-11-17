#include "GUIManager.h"
#include "GUIElement.h"
#include "Layout/GUILayout.h"
#include <iostream>

GUIManager::GUIManager(){

}

void GUIManager::DrawElements(){
	std::map<int,std::shared_ptr<GUIElement>>::iterator it;
	for (it = elements.begin();it != elements.end();it++){
		if (it->second->visable)it->second->Draw();
	}
}


int GUIManager::AddElement(std::shared_ptr<GUIElement> element,int id){
	if (id == -1)
		id = elements.size();
	element->SetId(id);
	elements.insert({id,element});
	return id;
}

void GUIManager::SetElementVisability(int id,bool visability){
	elements[id]->visable = visability;
}

void GUIManager::AddLayout(std::shared_ptr<GUILayout> layout){
	auto* layoutElements = layout->GetElementList();
	for (int i=0;i<layout->NumberOfElements();i++){
		AddElement((*layoutElements)[i],(*layoutElements)[i]->GetId());
	}
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

void GUIManager::Resize(int width,int height){
	for (auto element : elements){
		element.second->OnContextResize(width,height);
	}

}
