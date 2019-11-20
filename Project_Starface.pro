#-------------------------------------------------
#
# Project created Chishikii 2019-11-6
#
#-------------------------------------------------

include(../Common.pri)

TARGET = ProjectStarface

SOURCES += \
    heightmap.cpp \
    myscene.cpp \
    simplexnoise.cpp \
    terrain.cpp

HEADERS += \
    heightmap.h \
    simplexnoise.h \
    terrain.h

RESOURCES += \
    modelTextures/modeltextures.qrc \
    modelObjects/modelobjects.qrc \
    shader/shader.qrc
