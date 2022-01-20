#include "textObject.h"
#include <iostream>


Text::Text(int x, int y, float scale, std::string t, Window* window,std::string fontPath) : fontSize(scale),text(t),font(fontPath){

	FT_Init_FreeType(&library);
	xPos = x;
	yPos = y;

	if (!window)
		context = ((Window*)glfwGetWindowUserPointer(glfwGetCurrentContext()));
	else
		context = window;

	SetText(t);
}

Text::~Text(){
	for (Panel *p : characters)
		delete p;
}

void Text::OnContextResize(int contextW,int contextH){
	for (Panel* p : characters)
		p->OnContextResize(contextW,contextH);
}

//Set the text
void Text::SetText(std::string t){
	text = t;

	for (Panel *p : characters)
		delete p;

	characters.clear();

	FT_New_Face(library,font.c_str(),0,&face);
	FT_Set_Pixel_Sizes(face,0,fontSize);

	penX = xPos;
	penY = yPos;
	newLines = 0;

	for (char c : text)
		AddCharacter(c);

	width = penX-xPos;
	height = (face->size->metrics.height/2)/64;

	FT_Done_Face(face);
}

void Text::Draw(){
	for (auto character : characters)
		character->Draw();
}

void Text::AddCharacter(char c){
	FT_Load_Char(face,c,FT_LOAD_RENDER);

	if (c == '\n'){
		newLines++;
		penX = xPos;
		return;
	}

	if (c == '\t'){
		penX += face->size->metrics.max_advance/64;
		return;
	}


	//metrics are in 1/64th of a pixel

	int yOffset = (face->glyph->metrics.height - face->glyph->metrics.horiBearingY)/64 + newLines*(face->height/64)*newLineSpacing;

	Panel *p = new Panel(penX,penY-yOffset,face->glyph->metrics.width/64,face->glyph->metrics.height/64,context,vertShader,fragShader);
	p->SetColor(color[0],color[1],color[2],1.0);

	penX += (face->glyph->metrics.horiAdvance - face->glyph->metrics.horiBearingX)/64;

	GLuint tex = context->renderer.CreateTexture(face->glyph->bitmap.width,face->glyph->bitmap.rows,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer,GL_RED);

	p->SetTexture(tex);

	p->FlipY();

	characters.push_back(p);
}

void Text::SetPos(float x, float y){
	xPos = x;
	yPos = y;

	SetText(text);
}

void Text::SetFontSize(float size){
	fontSize = size;
	SetText(text);
}

void Text::SetTextColor(float r,float g, float b){
	color[0] = r;
	color[1] = g;
	color[2] = b;
	for (Panel* p : characters){
		p->SetColor(r,g,b,1.0);
	}

}
