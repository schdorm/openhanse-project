######################################################################
# Automatically generated by qmake (2.01a) Do. Aug 19 10:59:08 2010
######################################################################

TEMPLATE = app
TARGET = oh_control
DESTDIR = ../bin
DEPENDPATH += .
INCLUDEPATH += . ../networktools ../maphandling

LIBS += -L../networktools -loh_networktools \
	-L../maphandling -loh_maphandling

# Input
HEADERS += mainwindow.h mapthread.h
FORMS += MainWindow.ui
SOURCES += main.cpp mainwindow.cpp mapthread.cpp