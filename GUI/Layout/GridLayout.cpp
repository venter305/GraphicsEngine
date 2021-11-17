#include "GridLayout.h"

GridLayout::GridLayout(int x,int y,int _rows,int size,int padding) : numRows(_rows),cellSize(size),rowPadding(padding),GUILayout(x,y){
  for (int i=0;i<_rows;i++)
    rows.emplace_back(ListLayout::ListMode::Horizontal,x,y-i*(cellSize+padding));
}

void GridLayout::SetPadding(int xPad,int yPad){
  rowPadding = yPad;
  for (int i=0;i<numRows;i++){
    rows[i].SetPos(xPos,yPos-i*(cellSize+rowPadding));
    rows[i].SetPadding(xPad,yPad);
  }
}

int GridLayout::AddElementToRow(int row,std::shared_ptr<GUIElement> element,int id) {
  rows[row].AddElement(element,id);
  elements.push_back(element);
  return id;
}
