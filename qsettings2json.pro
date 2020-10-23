DEFINES += QT_NO_CAST_FROM_ASCII
INCLUDEPATH += .
SOURCES += main.cpp
TARGET = qsettings2json
TEMPLATE = app
CONFIG += console
QT -= gui

win32-msvc* {
  QMAKE_CXX_FLAGS += /std:c++17
}
