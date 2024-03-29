#pragma once

#include "panel.h"
#include "GUIElement.h"
#include <freetype2/ft2build.h>
#include <vector>

#include FT_FREETYPE_H

class Text : public GUIElement{
	public:
		struct Character{
			char charData;
			int xOff = 0;
			int yOff = 0;
			int linNum = 0;
			Panel *panel;
		};

		float fontSize;

		std::string text;
		std::string font;


		float color[3] = {0.0,0.0,0.0};

		Text(int,int,float,std::string,Window* window=nullptr,std::string="./GraphicsEngine/freefont/FreeSerif.otf");
		virtual ~Text();

		void Draw();
		void SetText(std::string_view);
		void SetSubText(int start, int len,std::string_view t);
		void SetPos(float,float);
		void SetFontSize(float);
		void SetTextColor(float,float,float);

		void SetNewLineSpacing(float spacing){newLineSpacing = spacing;SetText(text);}
		float GetNewLineSpacing(){return newLineSpacing;}

		virtual void MouseEventAction(Event &ev){};
		virtual void KeyEventAction(Event &ev){};

		virtual void OnContextResize(int contextW,int contextH);

		std::string GetText(){return text;};


private:
	std::string vertShader = "./GraphicsEngine/GUI/Shaders/panelVertShader";
	std::string fragShader = "./GraphicsEngine/GUI/Shaders/textFragShader";

	int penX,penY;
	int newLines = 0;
	int newLineSpacing = 1;
	std::vector<Character> characters;
	FT_Library library;
	FT_Face face;

	void AddCharacter(char);
	void SetCharacter(char c,int pos);
};
