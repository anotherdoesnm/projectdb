QT += core gui widgets designer uitools sql

CONFIG += c++17 console

TARGET = QtProject
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

# Определяем компилятор (GCC)
QMAKE_CXX = g++
QMAKE_CC = gcc
QMAKE_LINK = g++

# Добавляем флаги компиляции
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic
