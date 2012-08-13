SOURCES = main.cpp \
	  server.cpp \
serversocket.cpp \
servergamedata.cpp 
	
HEADERS += server.h\
serversocket.h \
servergamedata.h
	
TEMPLATE = app

LIBS += -L../common -loh_common \
	-L../networktools -loh_networktools \
	-L../gamedata -loh_gamedata

INCLUDEPATH +=	../common \
		../gamedata \
		../networktools

TARGET = oh_server

DESTDIR += ../bin

CONFIG += warn_on \
	  thread \
          qt

QT += xml \
      network

QT -= gui

# RESOURCES += default.qrc