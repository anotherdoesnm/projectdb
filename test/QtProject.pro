QT += core gui widgets designer uitools sql

CONFIG += c++17 console

TARGET = QtProject
TEMPLATE = app

SOURCES += main.cpp \
           dialog.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h \
    dialog.h

FORMS += mainwindow.ui \
    dialog.ui

# Определяем компилятор (GCC)
QMAKE_CXX = g++
QMAKE_CC = gcc
QMAKE_LINK = g++

# Добавляем флаги компиляции
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic

# Include SQLCipher
INCLUDEPATH += /mingw64/include  # Adjust if using 32-bit
LIBS += -L/mingw64/lib  # Adjust if using 32-bit
