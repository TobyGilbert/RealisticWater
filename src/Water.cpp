#include "Water.h"

#include <glm/gtc/type_ptr.hpp>

Water::Water(){
    createShader();
    init();
}

Water::~Water(){
    delete m_shaderProgram;
    delete m_model;
}

void Water::createShader(){
    m_shaderProgram = new ShaderProgram();
    m_vertShader = new Shader("shaders/waterVert.glsl", GL_VERTEX_SHADER);
    m_fragShader = new Shader("shaders/waterFrag.glsl", GL_FRAGMENT_SHADER);
    m_shaderProgram->attachShader(m_vertShader);
    m_shaderProgram->attachShader(m_fragShader);
    m_shaderProgram->bindFragDataLocation(0, "fragColour");
    m_shaderProgram->link();
    m_shaderProgram->use();

    m_reflectLoc = m_shaderProgram->getUniformLoc("reflect");
    m_refractLoc = m_shaderProgram->getUniformLoc("refract");

    // Create texture object
    glGenTextures(1, &m_reflectTex);
    glBindTexture(GL_TEXTURE_2D, m_reflectTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &m_refractTex);
    glBindTexture(GL_TEXTURE_2D, m_refractTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    glUniform1i(m_reflectLoc, 0);
    glUniform1i(m_refractLoc, 1);
}

void Water::init(){
    m_model = new Model("models/plane.obj");
}

void Water::loadMatricesToShader(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix){
    m_shaderProgram->use();
    GLuint MVPLoc = m_shaderProgram->getUniformLoc("MVP");

    glm::mat4 MVP = _projectionMatrix * _viewMatrix * _modelMatrix;

    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

}

void Water::render(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_reflectTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_refractTex);

    glBindVertexArray(m_model->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, m_model->getNumVerts());
    glBindVertexArray(0);
}

void Water::setReflectionTex(GLuint _texHandle){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texHandle);
    glUniform1i(m_reflectLoc, 0);
}

void Water::setRefractionTex(GLuint _texHandle){
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texHandle);
    glUniform1i(m_refractLoc, 1);
}
