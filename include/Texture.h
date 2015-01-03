#ifndef TEXTURE_H
#define TEXTURE_H
#ifdef DARWIN
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
    #include <GL/gl.h>
#endif
#include <iostream>
#include <IL/il.h>
#include <glm/glm.hpp>

class Texture{
public:
   Texture(std::string _path);
   ~Texture();
   void bind(GLuint _unit);
   GLuint getTextureID();
   void setParamater(GLenum _pname, GLenum _param);
private:
   GLuint m_textureID;

};
#endif
