#-------------------------------------------------
#
# Project created Chishikii 2019-11-6
#
#-------------------------------------------------

include(../Common.pri)

TARGET = ProjectStarface

SOURCES += \
    charactercontroller.cpp \
    heightmap.cpp \
    myscene.cpp \
    player.cpp \
    simplexnoise.cpp \
    terrain.cpp

HEADERS += \
    charactercontroller.h \
    heightmap.h \
    player.h \
    simplexnoise.h \
    terrain.h

RESOURCES += \
    modelTextures/modeltextures.qrc \
    modelObjects/modelobjects.qrc \
    shader/shader.qrc

DISTFILES +=
