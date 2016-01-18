TEMPLATE      = app
CONFIG          += qt warn_on
HEADERS          = BrowserNode.h BrowserView.h SynchroWindow.h SynchroDialog.h
SOURCES          = main.cpp BrowserNode.cpp SynchroWindow.cpp \
        BrowserView.cpp SynchroDialog.cpp Pixmap.cpp myio.cpp 


TARGET          = projectSynchro
DEFINES          = BooL=bool FALSE=false TRUE=true TR=tr
INCLUDEPATH   = 
QT += network  widgets
DESTDIR = ../../bin
