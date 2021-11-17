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

		Panel(GLuint,GLuint,GLuint,GLuint,Window* = nullptr,std::string="./GraphicsEngine/GUI/Shaders/panelVertShader",std::string="./GraphicsEngine/GUI/Shaders/panelFragShader");

		virtual ~Panel();

		virtual void Draw();
		virtual void OnContextResize(int w,int h);

		void SetTexture(GLuint);
		void CreateTexture(int width,int height,GLenum format,GLenum type, void* pixels);
		void UpdateTexture(int xOffset,int yOffset,int width,int height,GLenum format,GLenum type,void* pixels);
		void ChangeTextureParamater(GLenum,GLint);

		virtual void SetPos(float,float);
		virtual void SetSize(float,float);
		void SetColor(float,float,float,float);
		void SetColor(float _color[4]);
		void FlipY(bool state = true);
		void FlipX(bool state = true);

		void ChangeContext(GLFWwindow*);
		void SetShaders(std::string,std::string);
		bool CheckBoundingBox(int,int);
		virtual void MouseEventAction(Event& ev){};
		virtual void KeyEventAction(Event& ev){};

private:
		void SetMVP(int w,int h);
		void SetMVP();

};
