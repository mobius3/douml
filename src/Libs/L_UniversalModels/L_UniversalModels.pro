#-------------------------------------------------
#
# Project created by QtCreator 2012-11-30T17:04:40
#
#-------------------------------------------------

QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UniversalModels
TEMPLATE = lib
CONFIG+= build_all
TARGET = $$qtLibraryTarget(UniversalModels)


INCLUDEPATH += include \
            ../L_UniversalModels

QMAKE_CXXFLAGS += -std=gnu++11


DEFINES += L_TREE_CONTROLLER_LIBRARY

HEADERS += include/TreeModel.h \
    include/TreeItemInterface.h \
    include/l_tree_controller_global.h \
    include/AdaptingTableModel.h \
    include/TreeItem.h \
    include/TableDataInterface.h \
    include/TableDataListHolder.h \
    include/ItemController.h \
    include/treeviewfunctions.h \
    include/treeviewtemplatefunctions.h \
    include/treeitemfunctions.h \
    include/genericeventfilter.h

SOURCES += src/TreeModel.cpp \
    src/TreeItemInterface.cpp \
    src/AdaptingTableModel.cpp \
    src/TableDataInterface.cpp \
    src/AdaptingTableModelPrivate.cpp \
    src/treeviewfunctions.cpp \
    src/treeviewtemplatefunctions.cpp \
    src/genericeventfilter.cpp

Debug{
    MOC_DIR = .../.././build/MOC_debug/UniversalModels
    OBJECTS_DIR = ../../../build/Obj_debug/UniversalModels
    RCC_DIR = ../../../build/RCC_debug/UniversalModels
}

Release{
    MOC_DIR = ../../../build/MOC_release/UniversalModels
    OBJECTS_DIR = ../../../build/Obj_release/UniversalModels
    RCC_DIR = ../../../build/RCC_release/UniversalModels
}


    UI_DIR = UI
    DESTDIR = ../../../bin
