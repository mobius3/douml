TEMPLATE      = app
CONFIG          += qt warn_on debug
HEADERS          = BrowserNode.h BrowserView.h BrowserSearchDialog.h \
        ControlWindow.h UserDialog.h
SOURCES          = main.cpp BrowserNode.cpp ControlWindow.cpp \
        BrowserView.cpp Pixmap.cpp BrowserSearchDialog.cpp \
        UserDialog.cpp myio.cpp 


TARGET          = projectControl
DEFINES          = BooL=bool
INCLUDEPATH   = 
#The following line was inserted by qt3to4
QT += network  qt3support 
