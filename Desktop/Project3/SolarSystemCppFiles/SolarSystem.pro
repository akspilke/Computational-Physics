TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    celestialbody.cpp \
    euler.cpp \
    verlet.cpp \
    vec3.cpp \
    solarsystem.cpp

HEADERS += \
    celestialbody.h \
    euler.h \
    verlet.h \
    vec3.h \
    solarsystem.h
