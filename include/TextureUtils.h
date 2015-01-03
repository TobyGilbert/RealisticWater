#ifndef TEXTUREUTILS_H
#define TEXTUREUTILS_H

#ifdef DARWIN
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
    #include <GL/gl.h>
#endif
#include <iostream>
#include <IL/il.h>


class TextureUtils{
public:
   static GLuint createTexture(const GLchar* path);
};
#endif
