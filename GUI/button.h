#pragma once

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

		Button(int,int,int,int,void(*)(Button*),Window* = nullptr,std::string="./GraphicsEngine/GUI/panelVertShader",std::string="./GraphicsEngine/GUI/panelFragShader");
		virtual ~Button();
		void (*action)(Button*);
		virtual void MouseEventAction(Event& ev);
		virtual void KeyEventAction(Event& ev);

		std::string GetText(){return text->GetText();}

		void setText(std::string);
		void setTextSize(int);
		void setTextColor(float,float,float);
		void setTextAlignment(TextAlignment);
		void setTextPos(int = 0,int = 0);
		void draw();
		void setBackgroundColor(float,float,float);
		void SetTextMargins(int x, int y);

	private:
		int textMarginX = 0;
		int textMarginY = 0;
};
