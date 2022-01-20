#include "GUIManager.h"
#include "GUIElement.h"
#include "Layout/GUILayout.h"
#include <iostream>

GUIManager::GUIManager(){

}

void GUIManager::DrawElements(){
	std::map<int,std::shared_ptr<GUIElement>>::iterator it;
	for (auto[id,element] : elements){
		if (element->visable)element->Draw();
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
	for (auto [id,element] : elements){
		if (element->enableMouseEvents && ev.GetType()&(Event::MouseCursor|Event::MouseButton)){
			element->MouseEventAction(ev);
		}
		if (element->enableKeyEvents && ev.GetType()&(Event::Key|Event::Character))
			element->KeyEventAction(ev);
	}
}

void GUIManager::Resize(int width,int height){
	for (auto [id,element] : elements){
		element->OnContextResize(width,height);
	}

}
