#pragma once

#include <GLFW/glfw3.h>

class Renderer {
  public:

    Renderer();

    void DrawPolygon(int numIndices,GLuint vboId, GLuint iboId, GLuint shaderId, GLuint tex);

    GLuint CreateShaderId(const char *vCode, const char *fCode);

    GLuint CreateBuffer();
    void SetBufferData(GLuint bufId, GLenum target, size_t size, const void* data, GLenum usage);

    GLuint CreateTexture(int w, int h,GLenum format,GLenum type,void* pixels,GLenum internalFormat=GL_RGBA);
    void UpdateTexture(GLuint texId,int xOffset,int yOffset,int w,int h,GLenum format,GLenum type,void* pixels);
    void ChangeTextureParamater(GLuint texId,GLenum parameter,GLint value);

    void DeleteTexture(GLuint texId);
    void DeleteBuffer(GLuint bufId);
    void DeleteShader(GLuint shaderId);

    void SetUniformMatrix4fv(GLuint shaderId, const char *uniformName, const GLfloat *value, bool transpose = false);
    void SetUniform4f(GLuint shaderId, const char *uniformName, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);

};
