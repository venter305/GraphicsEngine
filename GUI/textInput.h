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

		TextInput(int,int,int,int,std::string t,std::function<void(TextInput*)> = nullptr,Window* = nullptr,std::string="./GraphicsEngine/GUI/Shaders/panelVertShader",std::string="./GraphicsEngine/GUI/Shaders/panelFragShader");

		void AddCharacter(char);
		void RemoveCharacter();
		void SetEnabled(bool);
		void SetEnabledColor(float[3]);
		void SetDisabledColor(float[3]);
		void SetStateColors(float[3],float[3]);
		void KeyInput(std::vector<int>);

		virtual void MouseEventAction(Event &ev);
		virtual void KeyEventAction(Event &ev);
		std::function<void(TextInput*)> DisableAction = nullptr;
};
