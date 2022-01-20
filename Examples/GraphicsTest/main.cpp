#include <iostream>
#include "GraphicsEngine/graphicsEngine.h"
#include "MainWindow.h"
#include "CanvasTest.h"

int main(){
	GraphicsEngine::Init();

	//GraphicsEngine::AddWindow(new MainWindow(640,480,"Graphics Test"));
	GraphicsEngine::AddWindow(new CanvasTest(640,480,"Canvas Test"));
	GraphicsEngine::Run();

	return 0;
}
