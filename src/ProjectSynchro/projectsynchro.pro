TEMPLATE = app

CONFIG -= app_bundle

CONFIG += qt warn_on c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS = \
    BrowserNode.h \
    BrowserView.h \
    SynchroWindow.h \
    SynchroDialog.h

SOURCES = \
    main.cpp \
    BrowserNode.cpp \
    SynchroWindow.cpp \
    BrowserView.cpp \
    SynchroDialog.cpp \
    Pixmap.cpp \
    myio.cpp

TARGET = projectSynchro
DEFINES += BooL=bool FALSE=false TRUE=true TR=tr
QT += network widgets

DESTDIR = ../../bin

UI_DIR = src/ui

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
