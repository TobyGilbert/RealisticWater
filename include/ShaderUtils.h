#ifndef SHADERUTILS_H
#define SHADERUTILS_H
#ifdef DARWIN
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
    #include <GL/gl.h>
#endif
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>


class shaderUtils{
public:
   static GLuint createShaderFromFile(const GLchar* path, GLenum shaderType);
};
#endif
