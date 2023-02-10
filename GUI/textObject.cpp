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
	for (auto &character : characters)
		delete character.panel;
}

void Text::OnContextResize(int contextW,int contextH){
	for (Character &character : characters)
		character.panel->OnContextResize(contextW,contextH);
}

//Set the text
void Text::SetText(std::string_view t){
	text = t;

	for (auto &character : characters)
		delete character.panel;
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

void Text::SetSubText(int start,int len,std::string_view t){
	if(start+len >= text.size())
		text.append((start+len)-text.size(),' ');
	text.replace(start,len,t);

	FT_New_Face(library,font.c_str(),0,&face);
	FT_Set_Pixel_Sizes(face,0,fontSize);

	for (int i=start;i<start+len;i++){
		if (i >= characters.size())
			AddCharacter(text[i]);
		else
			SetCharacter(text[i],i);
	}

	FT_Done_Face(face);
}

void Text::Draw(){
	for (auto& character : characters){
	 	character.panel->Draw();
	}
}

void Text::SetCharacter(char c,int pos){
	FT_Load_Char(face,c,FT_LOAD_RENDER);

	penX = characters[pos].panel->xPos;
	penY = characters[pos].panel->yPos;

	//TODO: control characters
	// if (c == '\n'){
	// 	newLines++;
	// 	penX = xPos;
	// 	return;
	// }
	//
	// if (c == '\t'){
	// 	penX += face->size->metrics.max_advance/64;
	// 	return;
	// }


	//int yOffset = (face->glyph->metrics.height - face->glyph->metrics.horiBearingY)/64 + newLines*(face->height/64)*newLineSpacing;

	delete characters[pos].panel;
	characters[pos].panel = new Panel(penX,penY,face->glyph->metrics.width/64,face->glyph->metrics.height/64,context,vertShader,fragShader);
	characters[pos].panel->SetColor(color[0],color[1],color[2],1.0);

	for (int i = pos+1;i<characters.size();i++){
		if (characters[i].linNum != characters[pos].linNum)
			break;
		characters[i].panel->xPos += (face->glyph->metrics.horiAdvance - face->glyph->metrics.horiBearingX)/64 - characters[pos].xOff;
	}

	characters[pos].xOff = (face->glyph->metrics.horiAdvance - face->glyph->metrics.horiBearingX)/64;
	GLuint tex = context->renderer.CreateTexture(face->glyph->bitmap.width,face->glyph->bitmap.rows,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer,GL_RED);

	characters[pos].panel->SetTexture(tex);

	characters[pos].panel->FlipY();


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
	Character character;
	character.linNum = newLines;
	character.yOff = (face->glyph->metrics.height - face->glyph->metrics.horiBearingY)/64 + newLines*(face->height/64)*newLineSpacing;

	character.panel = new Panel(penX,penY-character.yOff,face->glyph->metrics.width/64,face->glyph->metrics.height/64,context,vertShader,fragShader);
	character.panel->SetColor(color[0],color[1],color[2],1.0);

	penX += (face->glyph->metrics.horiAdvance - face->glyph->metrics.horiBearingX)/64;
	character.xOff = penX - character.panel->xPos;
	GLuint tex = context->renderer.CreateTexture(face->glyph->bitmap.width,face->glyph->bitmap.rows,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer,GL_RED);

	character.panel->SetTexture(tex);

	character.panel->FlipY();

	characters.push_back(character);

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
	for (auto &c : characters){
		c.panel->SetColor(r,g,b,1.0);
	}

}
