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

		Button(int,int,int,int,std::function<void(Button*)>,Window* = nullptr,std::string="./GraphicsEngine/GUI/Shaders/panelVertShader",std::string="./GraphicsEngine/GUI/Shaders/panelFragShader");
		virtual ~Button();
		//void (*action)(Button*);
		std::function<void(Button*)> action;
		virtual void MouseEventAction(Event& ev);
		virtual void KeyEventAction(Event& ev);
		virtual void OnContextResize(int contextW,int contextH);

		std::string GetText(){return text->GetText();}

		virtual void SetSize(float w,float h);
		virtual void SetPos(float x,float y);

		void SetText(std::string);
		void SetTextSize(int);
		void SetTextColor(float,float,float);
		void SetTextAlignment(TextAlignment);
		void SetTextPos(int = 0,int = 0);
		void Draw();
		void SetBackgroundColor(float,float,float);
		void SetBackgroundColor(float _color[4]);
		void SetHoveredColor(float,float,float);
		void SetHoveredColor(float _color[4]);
		void SetTextMargins(int x, int y);

	private:
		int textMarginX = 0;
		int textMarginY = 0;
};
