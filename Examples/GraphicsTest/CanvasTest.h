#pragma once

#include "GraphicsEngine/Window.h"
#include <cmath>
#include <ctime>

class CanvasTest : public Window{
	public:

		CanvasTest(int w,int h,std::string name):Window(w,h,name){
		}

		void OnStartup(){
			glClearColor(0.9f,0.9f,0.9f,1.0f);

			std::shared_ptr<Canvas> canvas = std::make_shared<Canvas>(0,baseHeight-350,baseWidth,350);
			canvas->DrawTriangle({163,305},{490,122},{173,16},4,{0,0,0});
			guiMan.AddElement(canvas,100);

			std::shared_ptr<ListLayout> controlList = std::make_shared<ListLayout>(ListLayout::ListMode::Horizontal,0,100);
			controlList->SetPadding(10,0);

			std::shared_ptr<Button> clearButton = std::make_shared<Button>(0,0,100,35,[&](Button *btn){
				auto canvas = guiMan.GetElement<Canvas>(100);
				canvas->ClearCanvas();
			});
			clearButton->SetBackgroundColor(0.8f,0.8f,0.8f);
			clearButton->SetText("Clear Canvas");
			controlList->AddElement(clearButton,200);

			std::srand(time(NULL));

			std::shared_ptr<Button> triButton = std::make_shared<Button>(0,0,100,35,[&](Button *btn){
				auto canvas = guiMan.GetElement<Canvas>(100);
				int w = canvas->width;
				int h = canvas->height;
				canvas->DrawTriangle({rand()%w,rand()%h},{rand()%w,rand()%h},{rand()%w,rand()%h},4,{0,0,0});
			});
			triButton->SetBackgroundColor(0.8f,0.8f,0.8f);
			triButton->SetText("Draw Triangle");
			controlList->AddElement(triButton,300);

			guiMan.AddLayout(controlList);
		}

		void OnUpdate(double dTime){
			glClear(GL_COLOR_BUFFER_BIT);
			guiMan.DrawElements();

		}

		void OnShutdown(){
		}

		bool mouseDown = false;
		double prevMouseX = 0;
		double prevMouseY = 0;

		void OnEvent(Event &ev){
			guiMan.HandleEvent(ev);


			switch (ev.GetType()){
        case Event::MouseButton:
	    		{
	    			MouseButtonEvent::ButtonType btnType = static_cast<MouseButtonEvent*>(&ev)->GetButtonType();
	    			MouseButtonEvent::ButtonState btnState = static_cast<MouseButtonEvent*>(&ev)->GetButtonState();
	    		  double mouseX = static_cast<MouseButtonEvent*>(&ev)->GetMouseX();
	    			double mouseY = static_cast<MouseButtonEvent*>(&ev)->GetMouseY();
	    			if(btnType == MouseButtonEvent::ButtonType::Left && btnState == MouseButtonEvent::ButtonState::Pressed){

	            mouseDown = true;
	            CanvasDraw(mouseX,mouseY);
	    			}
	          if(btnType == MouseButtonEvent::ButtonType::Left && btnState == MouseButtonEvent::ButtonState::Released){
	            mouseDown = false;
	          }
	    			break;
	    		}
        case Event::MouseCursor:
          {
            double mouseX = static_cast<MouseMoveEvent*>(&ev)->GetMouseX();
            double mouseY = static_cast<MouseMoveEvent*>(&ev)->GetMouseY();

						double currMouseX = prevMouseX;
						double currMouseY = prevMouseY;
						bool xOffset;
						bool yOffset;
						do{
							xOffset = std::abs(currMouseX-mouseX) > 0.1;
							yOffset = std::abs(currMouseY-mouseY) > 0.1;
							if (xOffset)
								currMouseX += (currMouseX-mouseX<0)?0.5f:-0.5f;
							if (yOffset)
								currMouseY += (currMouseY-mouseY<0)?0.5f:-0.5f;
            	CanvasDraw(currMouseX,currMouseY);
						}
						while(xOffset || yOffset);

            break;
          }
        default:
          break;
    	}
		}

		void CanvasDraw(int mouseX, int mouseY){
			auto canvas = guiMan.GetElement<Canvas>(100);
			if (canvas->CheckBoundingBox(mouseX,mouseY) && mouseDown){
				prevMouseX = mouseX;
				prevMouseY = mouseY;
				int leftEdge = canvas->xPos;
				int bottomEdge = canvas->yPos;

				int mouseCanvasX = (int)(mouseX-leftEdge);
				int mouseCanvasY = (int)(mouseY-bottomEdge);

				int lineWidth = 10;

				for (int k=lineWidth/-2;k<=lineWidth/2;k++){
					double xWidth = std::sqrt(pow(0.5,2)-pow((double)k/lineWidth,2))*(lineWidth);
					xWidth = std::round(xWidth);
					for (int j=xWidth*-1;j<xWidth;j++){
						for (int i=0;i<3;i++){
							float fadeVal = 1;
							int pixelX = (mouseCanvasX+j);
							if (pixelX >= canvas->width)
							 	pixelX = (canvas->width-1);
							int pixelY = (mouseCanvasY+k);
							int index = (pixelY+pixelX+i);

							if (canvas->GetPixel(pixelX,pixelY).red > 0)
								fadeVal = ((j>4||j<-4)||(k>4||k<-4)?0:0);
							if (pixelX < width && pixelX >= 0 && pixelY < height && pixelY >= 0){
								uint8_t value = ((j||k)?fadeVal:1);
								canvas->SetPixel(pixelX,pixelY,{value,value,value});
							}
						}
					}
				}
			}
			else
				mouseDown = false;
		}

};
