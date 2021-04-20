#pragma once
#include "GUILayout.h"

class ListLayout : public GUILayout{
  private:
    float paddingX = 0;
    float paddingY = 0;

  public:
    enum class ListMode{
      Vertical,
      Horizontal,
      None
    } mode = ListMode::None;

    ListLayout(ListMode mode,float x,float y);
    virtual ~ListLayout() = default;

    int AddElement(std::shared_ptr<GUIElement> element,int id = -1,int index = -1);
    void SetPadding(float xPad,float yPad);
};
