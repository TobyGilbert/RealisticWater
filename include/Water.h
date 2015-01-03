#ifndef __WATER_H_
#define __WATER_H_
#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "Model.h"
#include "Texture.h"
#include <QTime>
class Water{
public:
    Water();
    ~Water();
    void init();
    void loadMatricesToShader(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix);
    void render();
    GLuint getReflectLoc(){return m_reflectLoc;}
    GLuint getRefractLoc(){return m_refractLoc;}
    void setRefractionTex(GLuint _texHandle);
    void setReflectionTex(GLuint _texHandle);
    GLuint* getReflectTex(){return &m_reflectTex;}
    GLuint* getRefractTex(){return &m_refractTex;}
private:
    void createShader();
    ShaderProgram *m_shaderProgram;
    Shader *m_vertShader;
    Shader *m_fragShader;
    Model *m_model;
    GLuint m_reflectLoc;
    GLuint m_refractLoc;
    GLuint m_reflectTex;
    GLuint m_refractTex;
    Texture *m_normal;
    Texture *m_dudv;

    QTime m_timer;

    // time
    GLuint m_timeLoc;
};

#endif
