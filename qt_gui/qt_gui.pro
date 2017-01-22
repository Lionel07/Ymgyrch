QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_gui
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp

SOURCES += UI/MainWindow.cpp
HEADERS += UI/mainwindow.h
FORMS += UI/mainwindow.ui

SOURCES += UI/Debugger.cpp
HEADERS += UI/debugger.h
FORMS += UI/debugger.ui

SOURCES += UI/Renderer.cpp
HEADERS == UI/renderer.h
FORMS += UI/renderer.ui
