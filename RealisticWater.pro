TARGET=Realistic_water.out
OBJECTS_DIR=obj

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}
UI_HEADERS_DIR=ui
MOC_DIR=moc

CONFIG-=app_bundle
QT+=gui opengl core
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/Camera.cpp \
    src/ShaderUtils.cpp \
    src/TextureUtils.cpp \
    src/ShaderProgram.cpp \
    src/Texture.cpp \
    src/Model.cpp \
    src/OpenGLWidget.cpp \
    src/Shader.cpp \
    src/teapot.cpp \
    src/Water.cpp \
    src/Skybox.cpp


HEADERS += \
    include/mainwindow.h \
    include/Camera.h \
    include/ShaderUtils.h \
    include/TextureUtils.h \
    include/ShaderProgram.h \
    include/Texture.h \
    include/Model.h \
    include/OpenGLWidget.h \
    include/Shader.h \
    include/ui_mainwindow.h \
    include/teapot.h \
    include/Water.h \
    include/Skybox.h

INCLUDEPATH +=./include /opt/local/include
LIBS += -L/opt/local/lib -lIL -lassimp
DESTDIR=./

CONFIG += console
CONFIG -= app_bundle

# use this to suppress some warning from boost
QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/include/
# define the _DEBUG flag for the graphics lib

unix:LIBS += -L/usr/local/lib

# now if we are under unix and not on a Mac (i.e. linux) define GLEW
linux-*{
                linux-*:QMAKE_CXXFLAGS +=  -march=native
                linux-*:DEFINES+=GL42
                DEFINES += LINUX
}
DEPENDPATH+=include
# if we are on a mac define DARWIN
macx:DEFINES += DARWIN


FORMS += \
    ui/mainwindow.ui

OTHER_FILES += \
    shaders/PhongFrag.glsl \
    shaders/PhongVert.glsl \
    shaders/waterVert.glsl \
    shaders/waterFrag.glsl \
    models/newteapot.obj \
    models/plane.obj \
    shaders/OceanFrag.glsl \
    textures/skyCubeMap_negx.png \
    textures/skyCubeMap_negy.png \
    textures/skyCubeMap_negz.png \
    textures/skyCubeMap_posx.png \
    textures/skyCubeMap_posy.png \
    textures/skyCubeMap_posz.png \
    shaders/skyboxFrag.glsl \
    shaders/skyboxVert.glsl \
    shaders/reflectVert.glsl \
    textures/water_dudv.jpg \
    textures/water_normal.jpg
