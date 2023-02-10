#include <GL/glew.h>
#include <iostream>

#include "Renderer.h"


Renderer::Renderer(){

}

void Renderer::DrawPolygon(int numIndices, GLuint vboId, GLuint iboId, GLuint shaderId, GLuint tex){
  glUseProgram(shaderId);

	glBindBuffer(GL_ARRAY_BUFFER,vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iboId);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D,tex);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0,2,GL_FLOAT,false,4*sizeof(GLfloat),(void*)0);
	glVertexAttribPointer(1,2,GL_FLOAT,false,4*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

	glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,(void*)0);
}

GLuint Renderer::CreateShaderId(const char *vCode, const char *fCode){
  unsigned int vertex,fragment;

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex,1,&vCode,NULL);
  glCompileShader(vertex);

  int  success;
  char infoLog[512];
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if(!success){
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment,1,&fCode,NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  GLuint shaderId = glCreateProgram();
  glAttachShader(shaderId,vertex);
  glAttachShader(shaderId,fragment);
  glLinkProgram(shaderId);

  glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return shaderId;
}

GLuint Renderer::CreateBuffer() {
  GLuint tmp;
  glGenBuffers(1,&tmp);
  return tmp;
}

void Renderer::SetBufferData(GLuint bufId, GLenum target, size_t size, const void* data, GLenum usage){
  glBindBuffer(target, bufId);
	glBufferData(target, size, data, usage);
}

GLuint Renderer::CreateTexture(int w, int h,GLenum format,GLenum type,void* pixels,GLenum internalFormat){
  GLuint tex;
  glGenTextures(1,&tex);
  glBindTexture(GL_TEXTURE_2D,tex);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexImage2D(GL_TEXTURE_2D,0,internalFormat,w,h,0,format,type,pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  return tex;
}

GLuint Renderer::GenTexture(){
  GLuint tex;
  glGenTextures(1,&tex);
  return tex;
}

void Renderer::CopyTexture(GLuint srcName,GLenum srcTarget,GLint srcX,GLint srcY,GLuint dstName,GLenum dstTarget,GLint dstX,GLint dstY,GLsizei srcWidth,GLsizei srcHeight){
  glCopyImageSubData(srcName,srcTarget,0,srcX,srcY,0,dstName,dstTarget,0,dstX,dstY,0,srcWidth,srcHeight,0);
}

void Renderer::UpdateTexture(GLuint texId,int xOffset,int yOffset,int w,int h,GLenum format,GLenum type,void* pixels){
  glBindTexture(GL_TEXTURE_2D,texId);
	glTexSubImage2D(GL_TEXTURE_2D,xOffset,yOffset,0,w,h,format,type,pixels);
}

void Renderer::ChangeTextureParamater(GLuint texId,GLenum parameter,GLint value){
	glBindTexture(GL_TEXTURE_2D,texId);
	glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Renderer::DeleteTexture(GLuint texId){
  glDeleteTextures(1,&texId);
}
void Renderer::DeleteBuffer(GLuint bufId){
  glDeleteBuffers(1,&bufId);
}
void Renderer::DeleteShader(GLuint shaderId){
  glDeleteProgram(shaderId);
}


void Renderer::SetUniformMatrix4fv(GLuint shaderId, const char *uniformName, const GLfloat *value, bool transpose){
  glUseProgram(shaderId);
	int location = glGetUniformLocation(shaderId,uniformName);
	glUniformMatrix4fv(location,1,transpose,value);
}

void Renderer::SetUniform4f(GLuint shaderId, const char *uniformName, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4){
  glUseProgram(shaderId);
	int location = glGetUniformLocation(shaderId,uniformName);
	glUniform4f(location,value1,value2,value3,value4);
}

void Renderer::Enable(GLenum cap, GLuint index){
  glEnablei(cap,index);
}

void Renderer::Disable(GLenum cap, GLuint index){
  glDisablei(cap,index);
}

void Renderer::GetBoolean(GLenum cap, GLboolean *data){
  uint8_t val;
  glGetBooleanv(cap,&val);
  (*data) = val;
}
