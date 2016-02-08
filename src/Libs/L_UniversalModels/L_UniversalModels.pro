#-------------------------------------------------
#
# Project created by QtCreator 2012-11-30T17:04:40
#
#-------------------------------------------------

QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UniversalModels
TEMPLATE = lib
unix:CONFIG+= build_all staticlib
windows:CONFIG+= build_all
TARGET = $$qtLibraryTarget(UniversalModels)

INCLUDEPATH += include \
            ../L_UniversalModels

CONFIG += c++11


DEFINES += L_TREE_CONTROLLER_LIBRARY

HEADERS += include/AdaptingTableModel.h \
    include/AdaptingTableModelPrivate.h \
    include/genericeventfilter.h \
    include/ItemController.h \
    include/l_tree_controller_global.h \
    include/TableDataInterface.h \
    include/TableDataListHolder.h \
    include/treeitemfunctions.h \
    include/TreeItem.h \
    include/TreeItemInterface.h \
    include/TreeModel.h \
    include/treeviewfunctions.h \
    include/treeviewtemplatefunctions.h

SOURCES += src/AdaptingTableModel.cpp \
    src/AdaptingTableModelPrivate.cpp \
    src/genericeventfilter.cpp \
#   src/ItemController.cpp \
    src/TableDataInterface.cpp \
    src/TreeItemInterface.cpp \
    src/TreeModel.cpp \
    src/treeviewfunctions.cpp \
    src/treeviewtemplatefunctions.cpp

DESTDIR = ../../../bin

Release { CONFIG += release }
Debug { CONFIG += debug }

CONFIG(release, debug|release) {
    DEFINES += NDEBUG
    MOC_DIR = $${DESTDIR}/moc_release/UniversalModels
    OBJECTS_DIR = $${DESTDIR}/obj_release/UniversalModels
}

CONFIG(debug, debug|release) {
    DEFINES += TRACE DEBUG DEBUG_DOUML
    MOC_DIR = $${DESTDIR}/moc_debug/UniversalModels
    OBJECTS_DIR = $${DESTDIR}/obj_debug/UniversalModels
}
UI_DIR = UI
