QT += core gui widgets designer uitools sql

CONFIG += c++17 console

TEMPLATE = lib
CONFIG += plugin
QT += sql
TARGET = qsqlcipher

DEFINES += QT_SQL_SQLCIPHER
DEFINES += SQLITE_HAS_CODEC

INCLUDEPATH += 'C:\Users\Student04\Documents\GitHub\projectdb\test\plugins\sqldrivers\include'

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

# INCLUDEPATH += /mingw64/include
INCLUDEPATH += '/c/Program Files (x86)/OpenXLSX/include/OpenXLSX'
LIBS += -L"C:/Program Files (x86)/OpenXLSX/lib" -lopenxlsx

INCLUDEPATH += "C:\msys64\mingw64\sqldrivers\include"
LIBS += -L"C:\msys64\mingw64\sqldrivers" -lsqlcipher -lcrypto

INCLUDEPATH += "C:\Users\Student04\Documents\GitHub\projectdb\test\sqldrivers\include"
LIBS += -L"C:\Users\Student04\Documents\GitHub\projectdb\test\sqldrivers" -lsqlcipher -lcrypto
target.path = $C:/msys64/mingw64/sqldrivers/sqldrivers
INSTALLS += target
DEFINES += QT_SQL_CIPHER

