TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    celestialbody.cpp \
    vec3.cpp \
    euler.cpp

HEADERS += \
    vec3.h \
    celestialbody.h \
    euler.h
