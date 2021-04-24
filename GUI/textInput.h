#pragma once

#include "button.h"
#include "textObject.h"
#include <vector>
#include <functional>

class TextInput: public Button{
	public:

		std::string currText;
		bool enabled = false;
		float enabledColor[3] = {1,1,1};
		float disabledColor[3] = {1,1,1};
		double prevInTime;
		double inputTimer;
		double inTimeMax;
		std::string inputMask;

		TextInput(int,int,int,int,std::string t,std::function<void(TextInput*)> = nullptr,Window* = nullptr,std::string="./GraphicsEngine/GUI/panelVertShader",std::string="./GraphicsEngine/GUI/panelFragShader");

		void addCharacter(char);
		void removeCharacter();
		void setEnabled(bool);
		void setEnabledColor(float[3]);
		void setDisabledColor(float[3]);
		void setStateColors(float[3],float[3]);
		void keyInput(std::vector<int>);

		virtual void MouseEventAction(Event &ev);
		virtual void KeyEventAction(Event &ev);
		std::function<void(TextInput*)> disableAction = nullptr;
};
