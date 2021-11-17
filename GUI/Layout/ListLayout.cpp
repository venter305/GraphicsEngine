#include "ListLayout.h"

ListLayout::ListLayout(ListMode lMode,float x,float y) : mode(lMode), GUILayout(x,y){

}

int ListLayout::AddElement(std::shared_ptr<GUIElement> element,int id,int index){


  float baseX = xPos+element->xPos;
  float baseY = yPos+element->yPos-element->height;
  float x = baseX;
  float y = baseY;

  if (index == -1)
    index = elements.size();

  for(int i=0;i<elements.size() && i<index;i++){
      x += elements[i]->width + paddingX;
      y -= elements[i]->height + paddingY;
  }


  switch (mode){
    case ListMode::Vertical:
      element->SetPos(baseX,y);
      height += element->height;
      if (element->width < width)
        width = element->width;
      break;
    case ListMode::Horizontal:
      element->SetPos(x,baseY);
      width += element->width;
      if (element->height < height)
        height = element->height;
      break;
    case ListMode::None:
    default:
      element->SetPos(baseX,baseY);
      break;
  };
  element->SetId(id);

  std::vector<std::shared_ptr<GUIElement>>::iterator it = elements.begin()+index;
  elements.insert(it,element);

  return id;
}

void ListLayout::SetPadding(float xPad,float yPad){
  paddingX = xPad;
  paddingY = yPad;
}
