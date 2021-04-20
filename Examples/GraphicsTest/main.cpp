#include <iostream>
#include "GraphicsEngine/graphicsEngine.h"
#include "MainWindow.h"
#include "ElementTestWindow.h"

int main(){
	GraphicsEngine::Init();

	GraphicsEngine::AddWindow(new MainWindow(640,480,"Graphics Test"));
	//GraphicsEngine::AddWindow(new ElementTestWindow(640,480,"Element Test"));
	GraphicsEngine::Run();

	return 0;
}
