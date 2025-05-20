QT += core gui widgets designer uitools sql

CONFIG += c++17 console

TARGET = QtProject
TEMPLATE = app

SOURCES += main.cpp \
           dialog.cpp \
           exportexcel.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h \
    dialog.h \
    exportexcel.h

FORMS += mainwindow.ui \
    dialog.ui \
    exportexcel.ui

# Определяем компилятор (GCC)
QMAKE_CXX = g++
QMAKE_CC = gcc
QMAKE_LINK = g++

# Добавляем флаги компиляции
INCLUDEPATH += "C:/Program Files (x86)/OpenXLSX/include/OpenXLSX"
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic

# Include SQLCipher
# INCLUDEPATH += /mingw64/include
INCLUDEPATH += '/c/Program Files (x86)/OpenXLSX/include/OpenXLSX'
LIBS += -L"C:/Program Files (x86)/OpenXLSX/lib" -lopenxlsx
