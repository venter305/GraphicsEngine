#pragma once

#include <functional>
#include "panel.h"
#include "textObject.h"

class Button : public Panel{
	public:

		enum TextAlignment {
			Center = 0,
			Left = 1,
			Right = 2
		};

		//Text
		Text *text;

		TextAlignment textAlignment;

		GLuint textFbo;
		GLuint textTexture;

		float backgroundColor[4] = {1.0f,1.0f,1.0f,1.0f};
		float hoverColor[4] = {1.0f,1.0f,1.0f,1.0f};

		Button(int,int,int,int,std::function<void(Button*)>,Window* = nullptr,std::string="./GraphicsEngine/GUI/panelVertShader",std::string="./GraphicsEngine/GUI/panelFragShader");
		virtual ~Button();
		//void (*action)(Button*);
		std::function<void(Button*)> action;
		virtual void MouseEventAction(Event& ev);
		virtual void KeyEventAction(Event& ev);
		virtual void OnContextResize(int contextW,int contextH);

		std::string GetText(){return text->GetText();}

		virtual void setSize(float w,float h);
		virtual void setPos(float x,float y);

		void setText(std::string);
		void setTextSize(int);
		void setTextColor(float,float,float);
		void setTextAlignment(TextAlignment);
		void setTextPos(int = 0,int = 0);
		void draw();
		void setBackgroundColor(float,float,float);
		void setBackgroundColor(float _color[4]);
		void setHoveredColor(float,float,float);
		void setHoveredColor(float _color[4]);
		void SetTextMargins(int x, int y);

	private:
		int textMarginX = 0;
		int textMarginY = 0;
};
