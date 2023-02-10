#pragma once

#include "GraphicsEngine/graphicsEngine.h"
#include "CanvasTest.h"

class MainWindow : public Window{
	private:
		float bColor = 0.0f;
		bool inc =  false;
		int bCount = 0;
		bool checkboxBool = false;
	public:

		MainWindow(int w,int h,std::string name):Window(w,h,name){
		}

		void OnStartup(){
			glClearColor(0.9f,0.9f,0.9f,1.0f);

			int col1 = 0;
			int col2 = col1+150;

			int top = 380;

			float menuBarHeight = 25;

			std::shared_ptr<MenuBar> menuBar = std::make_shared<MenuBar>(0,baseHeight-menuBarHeight,baseWidth,menuBarHeight);
			menuBar->SetBackgroundColor(0.9f,0.9f,0.9f,1.0f);
			menuBar->SetMenuButtonColor(0.9f,0.9f,0.9f,1.0f);
			menuBar->SetMenuButtonPadding(10,2);
			menuBar->AddMenuButton("Canvas Test",[](Button *btn){
				GraphicsEngine::AddWindow(new CanvasTest(640,480,"Canvas Test"));
			});
			guiMan.AddElement(menuBar,500);

			std::shared_ptr<ListLayout> panelList = std::make_shared<ListLayout>(ListLayout::ListMode::Vertical,0,baseHeight-menuBarHeight);
			panelList->SetPadding(0,20);

			//Panel: basic tests
			std::shared_ptr<Panel> basic = std::make_shared<Panel>(0,0,10,10);
			basic->SetSize(100,100);
			basic->SetColor(1.0f,0.0f,0.0f,1.0f);
			panelList->AddElement(basic,0);

			//Panel: texture test
			std::shared_ptr<Panel> texPanel = std::make_shared<Panel>(0,0,100,100);
			texPanel->CreateTexture(100,100,GL_RGB,GL_FLOAT,nullptr);
			panelList->AddElement(texPanel,100);

			//Panel: alpha test
			std::shared_ptr<Panel> alphaPanel_back = std::make_shared<Panel>(30,0,50,50);
			alphaPanel_back->SetColor(0.0f,0.0f,1.0f,0.5f);
			panelList->AddElement(alphaPanel_back);
			std::shared_ptr<Panel> alphaPanel_front = std::make_shared<Panel>(0,40,50,50);
			alphaPanel_front->SetColor(1.0f,0.0f,0.0f,0.5f);
			panelList->AddElement(alphaPanel_front);

			guiMan.AddLayout(panelList);

			std::shared_ptr<ListLayout> textList = std::make_shared<ListLayout>(ListLayout::ListMode::Vertical,150,baseHeight-menuBarHeight-10);
			textList->SetPadding(0,100);

			//Text: basic test
			std::shared_ptr<Text> textBasic = std::make_shared<Text>(0,0,0,"NULL");
			textBasic->SetFontSize(20);
			textBasic->SetText("Basic Test");
			textList->AddElement(textBasic);

			std::string nlString = "Test\nNew Line Test\n\tTab Test";

			//Text: Format test
			std::shared_ptr<Text> formatText = std::make_shared<Text>(0,0,20,nlString);
			textList->AddElement(formatText);

			//Text: Color test
			std::shared_ptr<Text> colorText = std::make_shared<Text>(0,0,20,"Color Test");
			colorText->SetTextColor(1.0,0.0,0.0);
			textList->AddElement(colorText);

			guiMan.AddLayout(textList);

			std::shared_ptr<ListLayout> btnList = std::make_shared<ListLayout>(ListLayout::ListMode::Vertical,350,baseHeight-menuBarHeight-10);
			btnList->SetPadding(0,50);

			//Button: basic test
			std::shared_ptr<Button> btnBasic = std::make_shared<Button>(0,0,100,25,[&](Button *btn){
				bCount++;
			});
			btnBasic->SetBackgroundColor(0.8f,0.8f,0.8f);
			btnBasic->SetText("Button");
			btnBasic->SetTextSize(15);
			btnBasic->SetTextColor(0.0,0.0,0.0);
			btnList->AddElement(btnBasic);
			std::shared_ptr<Text> btnCount = std::make_shared<Text>(0,0,20,"Count: " + std::to_string(bCount));
			btnList->AddElement(btnCount,200);

			//Text Input: basic test
			std::shared_ptr<TextInput> textInBasic = std::make_shared<TextInput>(0,0,200,25,"Test");
			float enableColor[] = {1,1,1};
			float disableColor[] = {0.8f,0.8f,0.8};
			textInBasic->SetEnabledColor(enableColor);
			textInBasic->SetDisabledColor(disableColor);
			textInBasic->SetTextAlignment(Button::TextAlignment::Left);
			btnList->AddElement(textInBasic,300);

			std::shared_ptr<Text> textInOutput = std::make_shared<Text>(0,0,20,textInBasic->text->text);
			btnList->AddElement(textInOutput,400);


			std::shared_ptr<Checkbox> checkboxTest = std::make_shared<Checkbox>(0,0,12,12,&checkboxBool);
			checkboxTest->SetBackgroundColor(0.8f,0.8f,0.8f);
			btnList->AddElement(checkboxTest,600);

			std::shared_ptr<Text> checkboxText = std::make_shared<Text>(375,158,20,"Off");
			guiMan.AddElement(checkboxText,700);

			guiMan.AddLayout(btnList);
		}

		void OnUpdate(double dTime){
			glClear(GL_COLOR_BUFFER_BIT);

			float texData[100][100][3];

			float rColor = 0.0f;
			float gColor = 0.0f;

			for (int i=0;i<100;i++){
				for (int j=0;j<100;j++){
					texData[i][j][0] = rColor;
					texData[i][j][1] = gColor;
					texData[i][j][2] = bColor;
					if (gColor < 1.0f)
						gColor += (1.0f/100.0f);
				}
				gColor = 0;
				if (rColor < 1.0f)
					rColor += (1.0f/100.0f);
			}
			if (bColor < 1.0f && inc)
				bColor += (1.0f/255.0f);
			else if (bColor > 0.0f){
				inc = false;
				bColor -= (1.0f/255.0f);
			}
			else{
				inc = true;
				bColor = 0;
			}

			auto texPanel = guiMan.GetElement<Panel>(100);
			texPanel->UpdateTexture(0,0,100,100,GL_RGB,GL_FLOAT,texData);

			auto btnCount = guiMan.GetElement<Text>(200);
			btnCount->SetText("Count: "+std::to_string(bCount));

			auto textInBasic = guiMan.GetElement<TextInput>(300);
			if (!textInBasic->enabled){
				auto textInOutput = guiMan.GetElement<Text>(400);
				textInOutput->SetText(textInBasic->text->text);
			}

			auto checkboxText = guiMan.GetElement<Text>(700);
			checkboxText->SetText(checkboxBool?"On":"Off");

			guiMan.DrawElements();

		}

		void OnShutdown(){
		}

		void OnEvent(Event &ev){
			guiMan.HandleEvent(ev);
			swich(ev.GetType()){
				case Event::Key:
					{
						int keyCode = static_cast<KeyEvent*>(&ev)->GetKeyCode();
						int keyState = static_cast<KeyEvent*>(&ev)->GetKeyState();
						switch(keyCode){
							case GLFW_KEY_UP:
								rotD.z += 1;
								break;
							case GLFW_KEY_DOWN:
								rotD.z -= 1;
								break;

						}

						break;
					}
			}
		}
};
