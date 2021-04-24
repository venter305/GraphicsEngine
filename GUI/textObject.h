#pragma once

#include "panel.h"
#include "GUIElement.h"
#include <freetype2/ft2build.h>
#include <vector>

#include FT_FREETYPE_H

class Text : public GUIElement{
	public:

		float fontSize;

		std::string text;
		std::string font;


		float color[3] = {0.0,0.0,0.0};

		Text(int,int,float,std::string,Window* window=nullptr,std::string="./GraphicsEngine/freefont/FreeSerif.otf");
		virtual ~Text();

		void draw();
		void setText(std::string);
		void setPos(float,float);
		void setFontSize(float);
		void setTextColor(float,float,float);

		void SetNewLineSpacing(float spacing){newLineSpacing = spacing;setText(text);}
		float GetNewLineSpacing(){return newLineSpacing;}

		virtual void MouseEventAction(Event &ev){};
		virtual void KeyEventAction(Event &ev){};

		virtual void OnContextResize(int contextW,int contextH);

		std::string GetText(){return text;};


private:
	std::string vertShader = "./GraphicsEngine/GUI/panelVertShader";
	std::string fragShader = "./GraphicsEngine/GUI/textFragShader";

	int penX,penY;
	int newLines = 0;
	int newLineSpacing = 1;
	std::vector<Panel*> characters;
	FT_Library library;
	FT_Face face;

	void addCharacter(char);
};
