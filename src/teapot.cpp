#include "teapot.h"

#include <glm/gtc/type_ptr.hpp>

Teapot::Teapot(int _shader){
    createShader(_shader);
    init();
}

Teapot::~Teapot(){
    delete m_model;
    delete m_shaderProgram;;
}

void Teapot::createShader(int _shader){
    if (_shader == 0){
        m_shaderProgram = new ShaderProgram();
        m_vertShader = new Shader("shaders/reflectVert.glsl", GL_VERTEX_SHADER);
        m_fragShader = new Shader("shaders/PhongFrag.glsl", GL_FRAGMENT_SHADER);
        m_shaderProgram->attachShader(m_vertShader);
        m_shaderProgram->attachShader(m_fragShader);
        m_shaderProgram->bindFragDataLocation(0, "fragColour");
        m_shaderProgram->link();
        m_shaderProgram->use();

        delete m_vertShader;
        delete m_fragShader;

        m_phongProjLoc = m_shaderProgram->getUniformLoc("projectionMatrix");
        m_phongNormalLoc = m_shaderProgram->getUniformLoc("normalMatrix");
        m_phongMVPLoc = m_shaderProgram->getUniformLoc("modelViewProjectionMatrix");
        m_phongModelViewLoc = m_shaderProgram->getUniformLoc("modelViewMatrix");
        m_phongModelLoc = m_shaderProgram->getUniformLoc("modelMatrix");

        m_clipLoc = m_shaderProgram->getUniformLoc("clip");

        GLuint lightPosLoc = m_shaderProgram->getUniformLoc("light.position");
        GLuint lightIntLoc = m_shaderProgram->getUniformLoc("light.intensity");
        GLuint kdLoc = m_shaderProgram->getUniformLoc("Kd");
        GLuint kaLoc = m_shaderProgram->getUniformLoc("Ka");
        GLuint ksLoc = m_shaderProgram->getUniformLoc("Ks");
        GLuint shininessLoc = m_shaderProgram->getUniformLoc("shininess");

        glUniform4f(lightPosLoc, 1.0, 1.0, 1.0, 1.0);
        glUniform3f(lightIntLoc, 0.6, 0.7, 0.8);
        glUniform3f(kdLoc, 0.5, 0.5, 0.5);
        glUniform3f(kaLoc, 0.5, 0.5, 0.5);
        glUniform3f(ksLoc, 1.0, 1.0, 1.0);
        glUniform1f(shininessLoc, 100.0);
    }
    else{
        m_shaderProgram = new ShaderProgram();
        m_vertShader = new Shader("shaders/PhongVert.glsl", GL_VERTEX_SHADER);
        m_fragShader = new Shader("shaders/PhongFrag.glsl", GL_FRAGMENT_SHADER);
        m_shaderProgram->attachShader(m_vertShader);
        m_shaderProgram->attachShader(m_fragShader);
        m_shaderProgram->bindFragDataLocation(0, "fragColour");
        m_shaderProgram->link();
        m_shaderProgram->use();

        delete m_vertShader;
        delete m_fragShader;

        m_phongProjLoc = m_shaderProgram->getUniformLoc("projectionMatrix");
        m_phongNormalLoc = m_shaderProgram->getUniformLoc("normalMatrix");
        m_phongMVPLoc = m_shaderProgram->getUniformLoc("modelViewProjectionMatrix");
        m_phongModelViewLoc = m_shaderProgram->getUniformLoc("modelViewMatrix");
        m_phongModelLoc = m_shaderProgram->getUniformLoc("modelMatrix");

        m_clipLoc = m_shaderProgram->getUniformLoc("clip");

        GLuint lightPosLoc = m_shaderProgram->getUniformLoc("light.position");
        GLuint lightIntLoc = m_shaderProgram->getUniformLoc("light.intensity");
        GLuint kdLoc = m_shaderProgram->getUniformLoc("Kd");
        GLuint kaLoc = m_shaderProgram->getUniformLoc("Ka");
        GLuint ksLoc = m_shaderProgram->getUniformLoc("Ks");
        GLuint shininessLoc = m_shaderProgram->getUniformLoc("shininess");

        glUniform4f(lightPosLoc, 1.0, 1.0, 1.0, 1.0);
        glUniform3f(lightIntLoc, 0.6, 0.7, 0.8);
        glUniform3f(kdLoc, 0.5, 0.5, 0.5);
        glUniform3f(kaLoc, 0.5, 0.5, 0.5);
        glUniform3f(ksLoc, 1.0, 1.0, 1.0);
        glUniform1f(shininessLoc, 100.0);
    }
}

void Teapot::init(){
    m_model = new Model("models/newteapot.obj");
}

void Teapot::usePhong(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix){
    m_shaderProgram->use();
    // Calculate projection matrix

    glm::mat4 modelViewMatrix = _viewMatrix * _modelMatrix;
    glm::mat3 normalMatrix = glm::mat3(modelViewMatrix);
    normalMatrix = glm::inverse(normalMatrix);
    normalMatrix = glm::transpose(normalMatrix);
    glm::mat4 modelViewProjectionMatrix = _projectionMatrix * modelViewMatrix;

    glUniformMatrix4fv(m_phongModelLoc, 1, false, glm::value_ptr(_modelMatrix));
    glUniformMatrix4fv(m_phongModelViewLoc, 1, false, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(m_phongProjLoc, 1, false, glm::value_ptr(_projectionMatrix));
    glUniformMatrix3fv(m_phongNormalLoc, 1, false, glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(m_phongMVPLoc, 1, false, glm::value_ptr(modelViewProjectionMatrix));

}

void Teapot::render(){
    glBindVertexArray(m_model->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, m_model->getNumVerts());
    glBindVertexArray(0);
}
