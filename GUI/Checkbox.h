#pragma once

#include "button.h"

class Checkbox : public Button{
  public:
    bool *val = nullptr;

    Checkbox(int x,int y,int w,int h,bool *valPtr);
    virtual ~Checkbox() = default;

    virtual void MouseEventAction(Event& ev);

    bool IsChecked() {return *val;}
    void SetChecked(bool value);
};
