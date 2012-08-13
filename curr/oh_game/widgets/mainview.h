/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   oh.devs@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef _MainView_h
#define _MainView_h

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include <QtGui/QGraphicsView>

#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsPixmapItem>

#include <QtGui/QImage>

 #include <QtGui/QLabel>

#include <QtGui/QCheckBox>



#include "datamanager.h"

// #include "settings.h"
// #include "dataclass.h"
// #include "ship.h"
#include <AbstractMap>


// #include <math.h>

// const int const_mhiscale = 5;


class MainView : public QGraphicsView
{
  Q_OBJECT
  public:
    MainView(QWidget *parent = 0);
    ~MainView();
    
//     void setWorldmap(const QByteArray &data);
    
    
//     void showMap(const AbstractMap &map);
    
    // 	void starttimer(int);
    // 	bool schiffskollision(QGraphicsItem *);
    // 	bool kollision(QGraphicsItem*, QGraphicsItem*);
    // 	bool isLand( QGraphicsItem *) const;
    
    // 	void landing();
    // 	void activeLanding();
    
    void keyEventWeiterleitung(QKeyEvent *event);
    void rotateItem(QGraphicsItem *, double);
    // 	void questHandler(QString);
    
    // schiffsklasse activeship;		//Schiff, auf dem man gerade aktiv ist
    
    // DataClass *gamedata;
    // Settings *currentSettings;
    
    // int schwierigkeit;
    // bool tastatur;
    
    // bool anlegbar;
    
    // bool uhr;
    
    // bool cacheMaps;
    
    // int tageslaenge;			//Menge an Aktualisierungen fuer einen Spieltag
    
    
    // quint32 durchlauf;
    
    // QRgb schiffbar, nschiffbar, anlegestelle, strand_weich ,strand_hart;
    
    
    
    
    // QList <mapfarbdefstruct> farbdefliste;
    
    
    
    
    // QGraphicsPixmapItem *testschiff ;
    QImage collimg[3];
    // QList<QGraphicsPixmapItem*> schi
    // QList <QGraphicsItem *> hafenobjliste;
    QList <QGraphicsPixmapItem*> landobjektliste;
    
    
  public slots:
    void setWorldmap();
    
    void setWorldScene();
    void setDetailScene();
    
    
    void refresh();
//     void schuss();
    
//     void landgang();
    // 	void einschiffen();
    
//     void slotpause();
//     void endePause();
//     void startPause();
    
//     void segelsetzen(int);
    
    
  private:
    
    
//     ObjectGraphicsItem *m_activeModel;
//     QList <ObjectGraphicsItem *> modellist;
    
    
//     int zoomlvl;
    
    // QGraphicsScene *szene;
    // QGraphicsScene m_scene;
    
    // QGraphicsItem *graphicsitem_it;
    // QList <QGraphicsPixmapItem*> wolkenliste;
    // QGraphicsPixmapItem *wolke;
    // QGraphicsItem *objekte;
    
    // QImage *img;
    // QPixmap bgpixmap;
    // QBrush bgbrush;			//Hintergrundbrushzeugs
    // bool kartegeladen;
    
//     QTimer refreshGraphicsTimer;		//regelt neusetzen
//     int graphics_refresh_delay;		// time in ms, until the graphics are moved ...
    
    #ifndef _RELEASE_
    QLabel *knoten;
    QLabel *sollknoten;
    QLabel *sollsegel;
    QLabel *segel;
    QLabel *segeldir;
    QLabel *solldir;		//dir=direction = Richtung
    QLabel *dir;			
    QLabel *steuerdir;
    QLabel *sollsteuerdir;
    QLabel *winddir;
    QLabel *windv;
    QLabel *acclabel;
    
    QCheckBox *fokussieren;
    #endif
    
    bool pause;
    
    
    // const static double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628;
    //PI eben
    
    
  signals:
    void showWidget(int);
    void sig_enterBuilding(int);
    void sig_anlegbar(bool);
    // void nichtmehranlegen();
    void sig_trade();
    
    void sig_velocity(int);
    void sig_time();
    void sig_save();
    void gameMenuRequested();
    
    void sig_konsole();
    
    void appQuit();
    
  protected:
    void keyPressEvent(QKeyEvent *event);
    //     void mousePressEvent(QMouseEvent *event);
    
    void timerEvent(QTimerEvent *);
    
    QImage m_worldmap;
    
    QGraphicsScene *m_worldScene;
    QGraphicsScene *m_detailScene;
    
    int m_timerid;
    
    enum en_scene
    {
      null,
      world,
      detail
    } m_currentScene;
    
};

#endif
