SOURCES = gamedata.cpp \
	save.cpp \
	load.cpp \
	ohparameter.cpp \
	kontor.cpp \
	factory.cpp \
	city.cpp \
	cityproduction.cpp \
	citynames.cpp \
	player.cpp \
	ship.cpp \
	ohtime.cpp \
	wind.cpp \
	position.cpp \
	#shipfactory.cpp \
	shiptype.cpp \
buildings/market.cpp \
buildings/storagearea.cpp \
buildings/warehouse.cpp \
buildings/workerhouse.cpp \
xmlnames.cpp \
gamesettings.cpp
	
HEADERS += gamedata.h \
	ohparameter.h \
	kontor.h \
	factory.h \
	city.h \
	citynames.h \
	player.h \
	ship.h \
	ohtime.h \
	wind.h \
	position.h \
	#shipfactory.h \
	shiptype.h \
buildings/market.h \
buildings/storagearea.h \
buildings/warehouse.h \
buildings/workerhouse.h \
xmlnames.h \
gamesettings.h
	
	
TEMPLATE = lib

LIBS +=	-L../common -loh_common \
	-L../networktools -loh_networktools
INCLUDEPATH +=	../common \
		../networktools

TARGET = oh_gamedata
DESTDIR += . ../bin/lib

CONFIG += warn_on \
	  thread \
          qt

 QT += xml

QT -= gui
#network