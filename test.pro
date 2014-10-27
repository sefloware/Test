TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS +=

INCLUDEPATH += /home/pc/source
