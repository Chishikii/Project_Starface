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
    simplexnoise.cpp

HEADERS += \
    heightmap.h \
    simplexnoise.h

RESOURCES += \
    modelTextures/modeltextures.qrc \
    modelObjects/modelobjects.qrc
