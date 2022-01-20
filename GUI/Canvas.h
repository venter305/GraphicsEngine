#pragma once

#include "panel.h"

class Canvas : public Panel{
  public:
    struct Pixel{
      uint8_t red;
      uint8_t green;
      uint8_t blue;
    };

    struct Point{
      int x;
      int y;
    };

    Pixel backgroundColor = {255,255,255};

    uint8_t *pixels;

    Canvas(int,int,int,int,Window* = nullptr,std::string="./GraphicsEngine/GUI/Shaders/panelVertShader",std::string="./GraphicsEngine/GUI/Shaders/panelFragShader");
    ~Canvas();

    void Draw() override;

    Pixel GetPixel(int x, int y);
    void SetPixel(int x, int y, Pixel data);
    void ClearCanvas();
    void ClearCanvas(Pixel color);

    void DrawLine(Point p1,Point p2, int width, Pixel data);
    void DrawTriangle(Point p1, Point p2, Point p3, int width, Pixel data);
    void DrawTriangleFilled(Point p1, Point p2, Point p3, Pixel data);
};
