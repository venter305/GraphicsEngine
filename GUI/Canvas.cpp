#include "Canvas.h"

#define RENDERER context->renderer

Canvas::Canvas(int x,int y, int w, int h,Window* window,std::string vsName, std::string fsName): Panel(x,y,w,h,window,vsName,fsName){
  int numPixels = width*height*3;
  pixels = new uint8_t[numPixels];
  ClearCanvas();
  CreateTexture(width,height,GL_RGB,GL_UNSIGNED_BYTE,pixels);
}

Canvas::~Canvas(){
  delete[] pixels;
}

void Canvas::Draw(){
  UpdateTexture(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,pixels);
  Panel::Draw();
}

Canvas::Pixel Canvas::GetPixel(int x, int y){
  int index = (y*width+x)*3;
  if (index < width*height*3 && index >= 0)
    return {pixels[index],pixels[index+1],pixels[index+2]};
  return {0,0,0};
}

void Canvas::SetPixel(int x, int y, Pixel data){
  int index = (y*width+x)*3;
  if (index >= width*height*3 || index < 0)
    return;

  pixels[index] = data.red;
  pixels[index+1] = data.green;
  pixels[index+2] = data.blue;
}

void Canvas::ClearCanvas(){
  ClearCanvas(backgroundColor);
}

void Canvas::ClearCanvas(Pixel color){
  for (int y=0;y<height;y++)
    for (int x=0;x<width;x++)
      SetPixel(x,y,color);
}

float LerpY(Canvas::Point p1,Canvas::Point p2,int x){
  if (p1.x == p2.x)
    return -1;
  return p1.y+(x-p1.x)*((float)(p2.y-p1.y)/(p2.x-p1.x));
}

int LerpX(Canvas::Point p1,Canvas::Point p2,int y){
  if (p1.y == p2.y)
    return -1;
  return p1.x+(y-p1.y)*((float)(p2.x-p1.x)/(p2.y-p1.y));
}

void Canvas::DrawLine(Point p1, Point p2, int width,Pixel data){
  std::cout << p1.x << ' ' << p1.y << "  " << p2.x << ' ' << p2.y << std::endl;
  if (p1.x == p2.x){
    int startY = std::min(p1.y,p2.y);
    int endY = std::max(p1.y,p2.y);
    for (int y=startY;y<endY;y++){
      for (int w=width/-2;w<=width/2;w++){
        for (int h=width/-2;h<=width/2;h++){
          SetPixel(p1.x+w,y+h,data);
        }
      }
    }
    return;
  }
  int startX = std::min(p1.x,p2.x);
  int endX = std::max(p1.x,p2.x);
  for (int x=startX;x<=endX;x++){
    float y = LerpY(p1,p2,x);
    std::cout << x << ' ' << y << std::endl;
    for (int w=width/-2;w<=width/2;w++){
      for (int h=width/-2;h<=width/2;h++){
        SetPixel(x+w,y+h,data);
      }
    }
  }
}

void Canvas::DrawTriangle(Point p1, Point p2, Point p3, int width, Pixel data){
  DrawLine(p1,p2,width,data);
  DrawLine(p2,p3,width,data);
  DrawLine(p3,p1,width,data);
}


void Canvas::DrawTriangleFilled(Point p1, Point p2, Point p3, Pixel data){
  Point p[3] = {p1,p2,p3};
  for (int i=0;i<3;i++){
    if (p[0].y > p[1].y)
      std::swap(p[0],p[1]);
    if (p[1].y > p[2].y)
      std::swap(p[1],p[2]);
  }

  for (int y=p[0].y;y<=p[2].y;y++){
    if (y <= p[1].y){
      int x1 = LerpX(p[0],p[1],y);
      int x2 = LerpX(p[0],p[2],y);
      if (p[1].y == p[0].y)
        x1 = p[1].x;
      DrawLine({x1,y},{x2,y},1,data);
    }
    else{
      int x1 = LerpX(p[1],p[2],y);
      int x2 = LerpX(p[0],p[2],y);
      if (p[2].y == p[1].y)
        x1 = p[1].x;
      DrawLine({x1,y},{x2,y},1,data);
    }
  }

}
