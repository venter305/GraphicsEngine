#include <iostream>
#include "GraphicsEngine/graphicsEngine.h"

float bColor = 0.0f;
bool inc =  false;

int bCount = 0;

std::vector<Button*> buttons;
std::vector<TextInput*> textInputs;

void btn_action(Button* btn){
	bCount++;
}

void OnEvent(Event &ev){
	switch (ev.GetType()){
		case Event::Key:
			{
				int keyCode = static_cast<KeyEvent*>(&ev)->GetKeyCode();
				int keyState = static_cast<KeyEvent*>(&ev)->GetKeyState();
				if (keyState == KeyEvent::KeyState::Released)
					break;
				for (TextInput* tIn : textInputs){
					if(!tIn->enabled)
						continue;
					if (keyCode == GLFW_KEY_BACKSPACE)
						tIn->removeCharacter();
					else if (keyCode == GLFW_KEY_ENTER)
						tIn->setEnabled(false);
				}
			}
			break;
		case Event::Character:
			{
				unsigned int charCode = static_cast<CharEvent*>(&ev)->GetCharCode();
				for (TextInput* tIn : textInputs){
					if (!tIn->enabled)
						continue;
					tIn->addCharacter(charCode);
				}
			}
			break;
		case Event::MouseButton:
			MouseButtonEvent *mEv = static_cast<MouseButtonEvent*>(&ev);
			if (mEv->GetButtonType() != MouseButtonEvent::ButtonType::Left || mEv->GetButtonState() != MouseButtonEvent::ButtonState::Pressed)
				break;
			double xPos,yPos;
		  GraphicsEngine::input.GetMousePos(xPos,yPos);
			for (Button *btn : buttons){
				btn->clickAction(xPos,yPos);
			}
			break;
	}
}

void GUIinit(){

	int col1 = 0;
	int col2 = col1+150;

	int top = 380;

	//Panel: basic tests
	std::shared_ptr<Panel> basic = std::make_shared<Panel>(0,0,10,10);
	basic->setPos(col1,380);
	basic->setSize(100,100);
	basic->setColor(1.0f,0.0f,0.0f,1.0f);
	GraphicsEngine::guiMan.addElement(basic);

	//Panel: texture test
	std::shared_ptr<Panel> texPanel = std::make_shared<Panel>(col1,250,100,100);
	texPanel->CreateTexture(100,100,GL_RGB,GL_FLOAT,nullptr);
	GraphicsEngine::guiMan.addElement(texPanel,100);

	//Panel: alpha test
	std::shared_ptr<Panel> alphaPanel_back = std::make_shared<Panel>(col1+30,150,50,50);
	alphaPanel_back->setColor(0.0f,0.0f,1.0f,0.5f);
	GraphicsEngine::guiMan.addElement(alphaPanel_back);
	std::shared_ptr<Panel> alphaPanel_front = std::make_shared<Panel>(col1,120,50,50);
	alphaPanel_front->setColor(1.0f,0.0f,0.0f,0.5f);
	GraphicsEngine::guiMan.addElement(alphaPanel_front);

 //std::string fontPath = "./GraphicsEngine/freefont/FreeSerif.otf";

	//Text: basic test
	std::shared_ptr<Text> textBasic = std::make_shared<Text>(0,0,0,"NULL");
	textBasic->setPos(col2,450);
	textBasic->setFontSize(20);
	textBasic->setText("Basic Test");
	GraphicsEngine::guiMan.addElement(textBasic);

	std::string nlString = "Test\nNew Line Test\n\tTab Test";

	//Text: Format test
	std::shared_ptr<Text> formatText = std::make_shared<Text>(col2,400,20,nlString);
	GraphicsEngine::guiMan.addElement(formatText);

	//Text: Color test
	std::shared_ptr<Text> colorText = std::make_shared<Text>(col2,250,20,"Color Test");
	colorText->setTextColor(1.0,0.0,0.0);
	GraphicsEngine::guiMan.addElement(colorText);

	//Button: basic test
	std::shared_ptr<Button> btnBasic = std::make_shared<Button>(350,425,100,25,btn_action);
	btnBasic->setColor(0.8f,0.8f,0.8f,1.0f);
	btnBasic->setText("Button");
	btnBasic->setTextSize(15);
	btnBasic->setTextColor(0.0,0.0,0.0);
	buttons.push_back(btnBasic.get());
	GraphicsEngine::guiMan.addElement(btnBasic);
	std::shared_ptr<Text> btnCount = std::make_shared<Text>(480,425,20,"Count: " + std::to_string(bCount));
	GraphicsEngine::guiMan.addElement(btnCount,200);

	//Text Input: basic test
	std::shared_ptr<TextInput> textInBasic = std::make_shared<TextInput>(350,300,200,25,"Test");
	float enableColor[] = {1,1,1};
	float disableColor[] = {0.8f,0.8f,0.8};
	textInBasic->setEnabledColor(enableColor);
	textInBasic->setDisabledColor(disableColor);
	textInBasic->setTextAlignment(Button::TextAlignment::Left);
	buttons.push_back(textInBasic.get());
	textInputs.push_back(textInBasic.get());
	GraphicsEngine::guiMan.addElement(textInBasic,300);

	std::shared_ptr<Text> textInOutput = std::make_shared<Text>(350,250,20,textInBasic->text->text);
	GraphicsEngine::guiMan.addElement(textInOutput,400);

}

void renderLoop(GLFWwindow *window,double dTime){
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

	GLbyte test[10000*3];
	for (int i=0;i<30000;i++){
		test[i] = 255;
	}


	auto texPanel = std::static_pointer_cast<Panel>(GraphicsEngine::guiMan.elements[100]);
	texPanel->UpdateTexture(0,0,100,100,GL_RGB,GL_FLOAT,texData);

	auto btnCount = std::static_pointer_cast<Text>(GraphicsEngine::guiMan.elements[200]);
	btnCount->setText("Count: "+std::to_string(bCount));

	auto textInBasic = std::static_pointer_cast<TextInput>(GraphicsEngine::guiMan.elements[300]);

	if (!textInBasic->enabled){
		auto textInOutput = std::static_pointer_cast<Text>(GraphicsEngine::guiMan.elements[400]);
		textInOutput->setText(textInBasic->text->text);
	}

	GraphicsEngine::guiMan.drawElements();

}

int main(){

	GraphicsEngine::Init(640,480,"Graphics Test",renderLoop);
	glClearColor(0.9f,0.9f,0.9f,1.0f);

	GUIinit();

	GraphicsEngine::input.onEvent = OnEvent;
	GraphicsEngine::Run();

	return 0;
}
