SOURCES += data/abstractcity.cpp \
	data/goods.cpp \
	#data/abstractmap.cpp \
	data/abstractmapobject.cpp \
	data/building.cpp \
	libs/oqstring.cpp \
	libs/omath.cpp \
	libs/labels.cpp \
	libs/array2d.cpp \
	libs/point.cpp \
	libs/ovector.cpp \
	libs/ohsettingsdir.cpp
	
	
HEADERS += data/abstractcity.h \
	data/goods.h \
#	data/abstractmap.h \
	data/abstractmapobject.h \
	data/building.h \
	libs/oqstring.h \
	libs/omath.h \
	libs/labels.h \
	libs/array2d.h \
	libs/point.h \
	abstractcity.h \
	goods.h \
#	abstractmap.h \
	abstractmapobject.h \
	AbstractCity \
	Goods \
# 	AbstractMap \
	AbstractMapObject \
	OHBuilding \
	Building \
	oqstring.h \
	omath.h \
	labels.h \
	OQString \
	OMath \
	Labels \
	Array2D \
	libs/ovector.h \
	libs/ohsettingsdir.h \
	building.h
	
TEMPLATE = lib

TARGET = oh_common
DESTDIR += . ../bin/lib/

CONFIG += warn_on \
	  thread \
          qt

QT += xml
QT -= gui
