#pragma once

#include <string>
#include "GUIElement.h"

class Panel : public GUIElement{
	public:
		static GLfloat vertices[];

		static GLuint indices[];

		GLfloat color[4];

		//nt id;

		std::string vShader;
		std::string fShader;

		GLuint shaderId;
		GLuint vboId;
		GLuint iboId;

		GLuint fbo;
		GLuint tex = -1;

		bool flippedX = false;
		bool flippedY = false;

		Panel(GLuint,GLuint,GLuint,GLuint,Window* = nullptr,std::string="./GraphicsEngine/GUI/panelVertShader",std::string="./GraphicsEngine/GUI/panelFragShader");

		virtual ~Panel();

		virtual void draw();
		virtual void OnContextResize(int w,int h);

		void setTexture(GLuint);
		void CreateTexture(int width,int height,GLenum format,GLenum type, void* pixels);
		void UpdateTexture(int xOffset,int yOffset,int width,int height,GLenum format,GLenum type,void* pixels);
		void ChangeTextureParamater(GLenum,GLint);

		virtual void setPos(float,float);
		virtual void setSize(float,float);
		void setColor(float,float,float,float);
		void flipY(bool state = true);
		void flipX(bool state = true);

		void changeContext(GLFWwindow*);
		void setShaders(std::string,std::string);
		bool checkBoundingBox(int,int);
		virtual void MouseEventAction(Event& ev){};
		virtual void KeyEventAction(Event& ev){};

private:
		void SetMVP(int w,int h);
		void SetMVP();

};
