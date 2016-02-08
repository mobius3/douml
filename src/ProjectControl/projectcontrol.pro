TEMPLATE = app

CONFIG -= app_bundle

CONFIG += qt warn_on c++11

HEADERS = \
    BrowserNode.h \
    BrowserView.h \
    BrowserSearchDialog.h \
    ControlWindow.h \
    UserDialog.h

SOURCES = \
    main.cpp \
    BrowserNode.cpp \
    ControlWindow.cpp \
    BrowserView.cpp \
    Pixmap.cpp \
    BrowserSearchDialog.cpp \
    UserDialog.cpp \
    myio.cpp

TARGET = projectControl
DEFINES += BooL=bool FALSE=false TRUE=true TR=tr
QT += network widgets

DESTDIR = ../../bin

UI_DIR = src/ui

Debug { CONFIG += debug }
Release { CONFIG += release }

CONFIG(release, debug|release) {
    DEFINES += NDEBUG
    MOC_DIR = $${DESTDIR}/moc_release/$${TARGET}
    OBJECTS_DIR = $${DESTDIR}/obj_release/$${TARGET}
}

CONFIG(debug, debug|release) {
    DEFINES += TRACE DEBUG DEBUG_DOUML
    MOC_DIR = $${DESTDIR}/moc_debug/$${TARGET}
    OBJECTS_DIR = $${DESTDIR}/obj_debug/$${TARGET}
}
