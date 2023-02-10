#include "panel.h"

#include "../glm/glm/glm.hpp"
#include "../glm/glm/ext/matrix_clip_space.hpp"
#include "../glm/glm/ext/matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#define RENDERER context->renderer

GLfloat Panel::vertices[] = {
		 0.0f, 0.0f,0.0f,0.0f,
		 1.0f,0.0f,1.0f,0.0f,
		 1.0f, 1.0f,1.0f,1.0f,
		 0.0f, 1.0f,0.0f,1.0f,
		};

GLuint Panel::indices[] = {
			0,1,2,
			2,3,0
		};

Panel::Panel(GLuint x, GLuint y, GLuint w, GLuint h, Window* window,std::string vsName,std::string fsName) : vShader(vsName),fShader(fsName){
	//Init
	xPos = x;
	yPos = y;
	width = w;
	height = h;

	id = -1;
	enableMouseEvents = true;
	if (!window)
		context = ((Window*)glfwGetWindowUserPointer(glfwGetCurrentContext()));
	else
		context = window;
	float pixels[3] = {1.0f,1.0f,1.0f};
	CreateTexture(1,1,GL_RGB,GL_FLOAT,pixels);
	//Setup Context specific values
	//Shaders
	SetShaders(vShader,fShader);

	//Set the Model,view,projection matrices
	SetMVP();

	//Generate Buffers
	vboId = RENDERER.CreateBuffer();
	iboId = RENDERER.CreateBuffer();

	RENDERER.SetBufferData(vboId,GL_ARRAY_BUFFER,(sizeof(GLfloat)*16), vertices, GL_STATIC_DRAW);
	RENDERER.SetBufferData(iboId,GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*6, indices, GL_STATIC_DRAW);

	SetColor(1.0f,1.0f,1.0f,1.0f);
}

Panel::~Panel(){
	RENDERER.DeleteTexture(tex);
	RENDERER.DeleteBuffer(vboId);
	RENDERER.DeleteBuffer(iboId);
	RENDERER.DeleteShader(shaderId);
}

//Draw the Panel
void Panel::Draw(){
	RENDERER.DrawPolygon(6,vboId,iboId,shaderId,tex);
}

void Panel::OnContextResize(int w,int h){
	SetMVP(w,h);
}


//Set the position
void Panel::SetPos(float x,float y){
	xPos = x;
	yPos = y;
	SetMVP();
}

//Set the size
void Panel::SetSize(float w, float h){
	width = w;
	height = h;
	SetMVP();
}

void Panel::SetMVP(int contextW, int contextH){
	float aspectRatio = (float)contextW/(float)contextH;

	float x = xPos+width*flippedX;
	float y = yPos+height*flippedY;
	float w = width*(flippedX?-1:1);
	float h = height*(flippedY?-1:1);

	glm::mat4 proj = glm::ortho(0.0f,aspectRatio,0.0f,1.0f,-1.0f,1.0f);
	glm::mat4 view = glm::scale(glm::mat4(1.0f),glm::vec3(1/context->baseHeight,1/context->baseHeight,0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(x,y,0.0f));
	model = glm::scale(model,glm::vec3(w,h,1.0f));

	glm::mat4 mvp = proj*view*model;

	RENDERER.SetUniformMatrix4fv(shaderId,"mvp",&mvp[0][0]);
}

void Panel::SetMVP(){
	SetMVP(context->width,context->height);
}

//Set the texture
void Panel::SetTexture(GLuint texture){
	RENDERER.DeleteTexture(tex);
	tex = texture;
}

void Panel::CreateTexture(int w, int h,GLenum format,GLenum type,void* pixels){
	RENDERER.DeleteTexture(tex);
	tex = RENDERER.CreateTexture(w,h,format,type,pixels);
	texWidth = w;
	texHeight = h;
}

void Panel::UpdateTexture(int xOffset,int yOffset,int w,int h,GLenum format,GLenum type,void* pixels){
	RENDERER.UpdateTexture(tex,xOffset,yOffset,w,h,format,type,pixels);
}

void Panel::ChangeTextureParamater(GLenum parameter,GLint value){
	RENDERER.ChangeTextureParamater(tex,parameter,value);
}

void Panel::SetColor(float _color[4]){
	SetColor(_color[0],_color[1],_color[2],_color[3]);
}

//Set the Color tint of the texture
void Panel::SetColor(float r,float g,float b,float a){
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;

	RENDERER.SetUniform4f(shaderId,"color",color[0],color[1],color[2],color[3]);
}

void Panel::FlipX(bool state){
	flippedX = state;
	SetMVP();
}

void Panel::FlipY(bool state){
	flippedY = state;
	SetMVP();
}

void Panel::ChangeContext(GLFWwindow *window){
	//context = window;
	//GLFWwindow *currWindow = glfwGetCurrentContext();
	//glfwMakeContextCurrent(window);

	//Shaders
	SetShaders(vShader,fShader);

	//Set the Model,view,projection matrices
	SetMVP();

	//Generate Buffers
	vboId = RENDERER.CreateBuffer();
	iboId = RENDERER.CreateBuffer();

	RENDERER.SetBufferData(vboId,GL_ARRAY_BUFFER,(sizeof(GLfloat)*16), vertices, GL_STATIC_DRAW);
	RENDERER.SetBufferData(iboId,GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*6, indices, GL_STATIC_DRAW);
}

void Panel::SetShaders(std::string vsName, std::string fsName){
	//Shaders
	std::ifstream vsFile;
	std::ifstream fsFile;

	vsFile.open(vsName);
	fsFile.open(fsName);
	std::stringstream vsStream, fsStream;

	vsStream << vsFile.rdbuf();
	fsStream << fsFile.rdbuf();

	vsFile.close();
	fsFile.close();

	std::string vShader = vsStream.str();
	std::string fShader = fsStream.str();

	const char *vCode = vShader.c_str();
	const char *fCode = fShader.c_str();

	shaderId = RENDERER.CreateShaderId(vCode,fCode);
}

bool Panel::CheckBoundingBox(int x, int y){
	return (x >= xPos && x <= (xPos+width) && y >= yPos && y <= (yPos+height));
}
