SOURCES = admsocket.cpp \
ohsocket.cpp \
networkcommands.cpp
	
HEADERS += admsocket.h\
ohsocket.h \
networkcommands.h
	
TEMPLATE = lib

# NOT needed:
##
#LIBS += -L../common -loh_common
##
###	-L../gamedata -loh_gamedata
##
#INCLUDEPATH += ../common
##
###	       ../gamedata
##

TARGET = oh_networktools

DESTDIR += . ../bin/lib

CONFIG += warn_on \
          qt

QT += network
QT -= gui

