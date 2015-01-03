#include <QGuiApplication>

#include "OpenGLWidget.h"
#include <iostream>

const static float INCREMENT=0.01;
//------------------------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//------------------------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.1;
OpenGLWidget::OpenGLWidget(const QGLFormat _format, QWidget *_parent) : QGLWidget(_format,_parent){
    // set this widget to have the initial keyboard focus
    setFocus();
    // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
    m_rotate=false;
    // mouse rotation values set to 0
    m_spinXFace=0;
    m_spinYFace=0;
    // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
    this->resize(_parent->size());
}
//----------------------------------------------------------------------------------------------------------------------
OpenGLWidget::~OpenGLWidget(){
    delete m_cam;
    delete m_teapot;
    delete m_water;
}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::initializeGL(){

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    glEnable(GL_MULTISAMPLE);

    //glEnable(GL_CLIP_DISTANCE0);


    // as re-size is not explicitly called we need to do this.
    glViewport(0,0,width(),height());

    // Initialize the camera
    m_cam = new Camera(glm::vec3(0.0, 1.0, 5.0));

    // initialize the water
    m_teapot = new Teapot();
    m_water = new Water();

    genFBOs();

    startTimer(0);
}

//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::resizeGL(const int _w, const int _h){
    // set the viewport for openGL
    glViewport(0,0,_w,_h);
    m_cam->setShape(_w, _h);

}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::timerEvent(QTimerEvent *){
    updateGL();
}

void OpenGLWidget::genFBOs(){
    // Gen framebuffer
    glGenFramebuffers(1, &m_reflectFB);
    glBindFramebuffer(GL_FRAMEBUFFER, m_reflectFB);

    // Bind texture to FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *(m_water->getReflectTex()), 0);

    // Set the targets for the fragment shader output
    GLenum drawBufs[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBufs);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Gen framebuffer
    glGenFramebuffers(1, &m_refractFB);
    glBindFramebuffer(GL_FRAMEBUFFER, m_refractFB);

    // Bind texture to FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,*(m_water->getRefractTex()), 0);

    // Set the targets for the fragment shader output
    glDrawBuffers(1, drawBufs);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGLWidget::renderReflections(){
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 512, 512);

    glm::mat4 rotx;
    glm::mat4 roty;

    rotx = glm::rotate(rotx, m_spinXFace, glm::vec3(1.0, 0.0, 0.0));
    roty = glm::rotate(roty, m_spinYFace, glm::vec3(0.0, 1.0, 0.0));

    m_mouseGlobalTX = rotx*roty;
    // add the translations
    m_mouseGlobalTX[3][0] = m_modelPos.x;
    m_mouseGlobalTX[3][1] = m_modelPos.y;
    m_mouseGlobalTX[3][2] = m_modelPos.z;
    glm::mat4 modelMatrix = glm::mat4();m_mouseGlobalTX;

    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0, -1.0, 1.0));
    m_teapot->usePhong(modelMatrix, m_cam->getViewMatrix(), m_cam->getProjectionMatrix());
    m_teapot->render();
}

void OpenGLWidget::renderRefractions(){
    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 512, 512);

    glm::mat4 rotx;
    glm::mat4 roty;

    rotx = glm::rotate(rotx, m_spinXFace, glm::vec3(1.0, 0.0, 0.0));
    roty = glm::rotate(roty, m_spinYFace, glm::vec3(0.0, 1.0, 0.0));

    m_mouseGlobalTX = rotx*roty;
    // add the translations
    m_mouseGlobalTX[3][0] = m_modelPos.x;
    m_mouseGlobalTX[3][1] = m_modelPos.y;
    m_mouseGlobalTX[3][2] = m_modelPos.z;
    glm::mat4 modelMatrix = glm::mat4();m_mouseGlobalTX;

    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0, 1.0, 1.0));
    m_teapot->usePhong(modelMatrix, m_cam->getViewMatrix(), m_cam->getProjectionMatrix());
    m_teapot->render();
}

//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::paintGL(){
    glBindFramebuffer(GL_FRAMEBUFFER, m_reflectFB);
    renderReflections();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, m_refractFB);
    renderRefractions();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, width()*2, height()*2);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 rotx;
    glm::mat4 roty;

    rotx = glm::rotate(rotx, m_spinXFace, glm::vec3(1.0, 0.0, 0.0));
    roty = glm::rotate(roty, m_spinYFace, glm::vec3(0.0, 1.0, 0.0));

    m_mouseGlobalTX = rotx*roty;
    // add the translations
    m_mouseGlobalTX[3][0] = m_modelPos.x;
    m_mouseGlobalTX[3][1] = m_modelPos.y;
    m_mouseGlobalTX[3][2] = m_modelPos.z;
    glm::mat4 modelMatrix = m_mouseGlobalTX;

    modelMatrix = glm::rotate(modelMatrix, 90.0f ,glm::vec3(1.0, 0.0, 0.0));
    m_water->loadMatricesToShader(modelMatrix, m_cam->getViewMatrix(), m_cam->getProjectionMatrix());
    m_water->render();


}

//------------------------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::mouseMoveEvent (QMouseEvent *_event){
  // Sourced from Jon Macey's NGL library
  // note the method buttons() is the button state when event was called
  // this is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if(m_rotate && _event->buttons() == Qt::LeftButton){
    int diffx=_event->x()-m_origX;
    int diffy=_event->y()-m_origY;
    m_spinXFace += (float) 0.5f * diffy;
    m_spinYFace += (float) 0.5f * diffx;
    m_origX = _event->x();
    m_origY = _event->y();
  }
        // right mouse translate code
  else if(m_translate && _event->buttons() == Qt::RightButton){
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos=_event->x();
    m_origYPos=_event->y();
    m_modelPos.x += INCREMENT * diffX;
    m_modelPos.y -= INCREMENT * diffY;
   }
}
//------------------------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::mousePressEvent ( QMouseEvent * _event){
    // Sourced from Jon Macey's NGL library
  // this method is called when the mouse button is pressed in this case we
  // store the value where the mouse was clicked (x,y) and set the Rotate flag to true
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate = true;
  }
  // right mouse translate mode
  else if(_event->button() == Qt::RightButton)
  {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_translate = true;
  }

}
//------------------------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::mouseReleaseEvent ( QMouseEvent * _event ){
    // Sourced from Jon Macey's NGL library
  // this event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_rotate=false;
  }
        // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_translate=false;
  }
}
//------------------------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::wheelEvent(QWheelEvent *_event){
    // Sourced from Jon Macey's NGL library
    // check the diff of the wheel position (0 means no change)
    if(_event->delta() > 0)
    {
        m_modelPos.z+=ZOOM;
    }
    else if(_event->delta() <0 )
    {
        m_modelPos.z-=ZOOM;
    }
}

