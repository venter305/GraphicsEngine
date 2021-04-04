#include "textObject.h"
#include <iostream>


Text::Text(int x, int y, float scale, std::string t, Window* window,std::string fontPath) : xPos(x),yPos(y),fontSize(scale),text(t),font(fontPath){

	FT_Init_FreeType(&library);

	setText(t);
}

Text::~Text(){
	for (Panel *p : characters)
		delete p;
}
//Set the text
void Text::setText(std::string t){
	text = t;

	for (Panel *p : characters)
		delete p;

	characters.clear();

	FT_New_Face(library,font.c_str(),0,&face);
	FT_Set_Pixel_Sizes(face,0,fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	penX = xPos;
	penY = yPos;
	newLines = 0;

	for (char c : text)
		addCharacter(c);

	width = penX-xPos;
	height = (face->size->metrics.height/2)/64;

	FT_Done_Face(face);
}

void Text::draw(){
	for (auto character : characters)
		character->draw();
}

void Text::addCharacter(char c){
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

	int yOffset = (face->glyph->metrics.height - face->glyph->metrics.horiBearingY)/64 + newLines*(face->height/64);

	Panel *p = new Panel(penX,penY-yOffset,face->glyph->metrics.width/64,face->glyph->metrics.height/64,context,vertShader,fragShader);
	p->setColor(color[0],color[1],color[2],1.0);

	penX += (face->glyph->metrics.horiAdvance - face->glyph->metrics.horiBearingX)/64;

	GLuint tex;

	glGenTextures(1,&tex);
	glBindTexture(GL_TEXTURE_2D,tex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RED,face->glyph->bitmap.width,face->glyph->bitmap.rows,0,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	p->setTexture(tex);

	p->flipY();

	characters.push_back(p);
}

void Text::setPos(int x, int y){
	xPos = x;
	yPos = y;

	setText(text);
}

void Text::setFontSize(float size){
	fontSize = size;
	setText(text);
}

void Text::setTextColor(float r,float g, float b){
	color[0] = r;
	color[1] = g;
	color[2] = b;
	for (Panel* p : characters){
		p->setColor(r,g,b,1.0);
	}

}
