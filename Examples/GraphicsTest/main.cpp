#include <iostream>
#include "GraphicsEngine/graphicsEngine.h"

class MainWindow : public Window{
	private:
		float bColor = 0.0f;
		bool inc =  false;
		int bCount = 0;
	public:

		MainWindow(int w,int h,std::string name):Window(w,h,name){
		}

		void OnStartup(){
			glClearColor(0.9f,0.9f,0.9f,1.0f);

			int col1 = 0;
			int col2 = col1+150;

			int top = 380;

			//Panel: basic tests
			std::shared_ptr<Panel> basic = std::make_shared<Panel>(0,0,10,10);
			basic->setPos(col1,380);
			basic->setSize(100,100);
			basic->setColor(1.0f,0.0f,0.0f,1.0f);
			guiMan.addElement(basic,0);

			//Panel: texture test
			std::shared_ptr<Panel> texPanel = std::make_shared<Panel>(col1,250,100,100);
			texPanel->CreateTexture(100,100,GL_RGB,GL_FLOAT,nullptr);
			guiMan.addElement(texPanel,100);

			//Panel: alpha test
			std::shared_ptr<Panel> alphaPanel_back = std::make_shared<Panel>(col1+30,150,50,50);
			alphaPanel_back->setColor(0.0f,0.0f,1.0f,0.5f);
			guiMan.addElement(alphaPanel_back);
			std::shared_ptr<Panel> alphaPanel_front = std::make_shared<Panel>(col1,120,50,50);
			alphaPanel_front->setColor(1.0f,0.0f,0.0f,0.5f);
			guiMan.addElement(alphaPanel_front);

			//Text: basic test
			std::shared_ptr<Text> textBasic = std::make_shared<Text>(0,0,0,"NULL");
			textBasic->setPos(col2,450);
			textBasic->setFontSize(20);
			textBasic->setText("Basic Test");
			guiMan.addElement(textBasic);

			std::string nlString = "Test\nNew Line Test\n\tTab Test";

			//Text: Format test
			std::shared_ptr<Text> formatText = std::make_shared<Text>(col2,400,20,nlString);
			guiMan.addElement(formatText);

			//Text: Color test
			std::shared_ptr<Text> colorText = std::make_shared<Text>(col2,250,20,"Color Test");
			colorText->setTextColor(1.0,0.0,0.0);
			guiMan.addElement(colorText);

			//Button: basic test
			std::shared_ptr<Button> btnBasic = std::make_shared<Button>(350,425,100,25,[&](Button *btn){
				bCount++;
			});
			btnBasic->setColor(0.8f,0.8f,0.8f,1.0f);
			btnBasic->setText("Button");
			btnBasic->setTextSize(15);
			btnBasic->setTextColor(0.0,0.0,0.0);
			guiMan.addElement(btnBasic);
			std::shared_ptr<Text> btnCount = std::make_shared<Text>(480,425,20,"Count: " + std::to_string(bCount));
			guiMan.addElement(btnCount,200);

			//Text Input: basic test
			std::shared_ptr<TextInput> textInBasic = std::make_shared<TextInput>(350,300,200,25,"Test");
			float enableColor[] = {1,1,1};
			float disableColor[] = {0.8f,0.8f,0.8};
			textInBasic->setEnabledColor(enableColor);
			textInBasic->setDisabledColor(disableColor);
			textInBasic->setTextAlignment(Button::TextAlignment::Left);
			guiMan.addElement(textInBasic,300);

			std::shared_ptr<Text> textInOutput = std::make_shared<Text>(350,250,20,textInBasic->text->text);
			guiMan.addElement(textInOutput,400);
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
			btnCount->setText("Count: "+std::to_string(bCount));

			auto textInBasic = guiMan.GetElement<TextInput>(300);
			if (!textInBasic->enabled){
				auto textInOutput = guiMan.GetElement<Text>(400);
				textInOutput->setText(textInBasic->text->text);
			}

			guiMan.drawElements();

		}

		void OnShutdown(){
		}

		void OnEvent(Event &ev){
			guiMan.HandleEvent(ev);
		}

};

int main(){
	GraphicsEngine::Init();

	GraphicsEngine::AddWindow(new MainWindow(640,480,"Graphics Test"));
	GraphicsEngine::Run();

	return 0;
}
