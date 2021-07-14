#pragma once

#include "GUILayout.h"
#include "ListLayout.h"

class GridLayout : public GUILayout{
  private:
    float rowPadding = 0;
    int numRows = 0;
    int cellSize = 0;

    std::vector<ListLayout> rows;

  public:
    GridLayout(int x,int w,int rows,int size,int padding);
    virtual ~GridLayout() = default;

    void SetPadding(int xPad,int yPad);
    int AddElementToRow(int row,std::shared_ptr<GUIElement> element,int id = -1);
};
