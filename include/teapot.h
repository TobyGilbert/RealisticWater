#ifndef __TEAPOT_H_
#define __TEAPOT_H_

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Model.h"

class Teapot{
public:
    Teapot();
    ~Teapot();
    void init();
    void render();
    void usePhong(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix);
    void useReflect(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix);
    void useRefract(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix);
private:
    void createShader();
    void createRefractShader();
    void createReflectShader();
    Model *m_model;
    ShaderProgram *m_shaderProgram;
    ShaderProgram *m_refractProgram;
    ShaderProgram *m_reflectProgram;
    Shader *m_vertShader;
    Shader *m_fragShader;

    //Unifrom locations
    GLuint m_phongProjLoc;
    GLuint m_phongModelLoc;
    GLuint m_phongNormalLoc;
    GLuint m_phongMVPLoc;
    GLuint m_phongModelViewLoc;



};

#endif
