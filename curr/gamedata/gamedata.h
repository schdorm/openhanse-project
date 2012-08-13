/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
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

#ifndef _GAME_DATA_CLASS_H
#define _GAME_DATA_CLASS_H


#include "player.h"
#include "city.h"

#include <QtCore/QThread>
#include <QtCore/QTimer>
#include <QtCore/QVariant>

#include <QtCore/QQueue>

#include "wind.h"
#include "ohparameter.h"
 
// class Object;
// class City;
class Time;
class QXmlStreamReader;
// class Kontor;
// class Ship;
// class Person;
// class Building;
// class Factory;
// class Map;

/*namespace Filters
{
  enum Filters
  {
    NoFilter,
    Coordinates,
    Objecttype,
    Buildingtype
  };
}*/

class GameData : public QThread
{
  Q_OBJECT
  public:
    GameData(QObject * = 0);
//     ~GameData();
//     void loadDefaultCitys();
    void newGame();
    
    /*virtual */void addPlayer(Player *);
    void addCity(City *);
    
    void loadData(const QByteArray &);
    void loadItems(QXmlStreamReader *, int, bool);



    void save(QByteArray *) const;
    void save(QString, const QPoint &) const;
    
    const QHash<int, City*> * cityHash () const	{	return &m_CityHash;	}
    
    
    QList <City*> cityList	()	const	{	return m_CityHash.values();	}
    QList <Player*> playerList	()	const	{	return m_Players.values();	}
    Player * player		(int id)const	{	return m_Players.value(id, m_defaultPlayer);	}
    const Player * defaultPlayer()	const	{	return m_defaultPlayer;		}
    bool playerExists		(int id)const	{	return m_Players.contains(id);	}

    const Wind * wind		()	const	{	return m_wind;		}
    Wind *wind			()		{	return m_wind;		}
    
    int currentPlayers		()	const { return m_currentPlayers;}
    int maxPlayers		()	const { return m_maxPlayers;}
    void setMaxPlayers		(int count);
//     void setCurrentPlayers(int count);
    
    
    
//   public slots:
//     void calcData();
//     void startTimer();
//     void stopTimer();
//     void loadData(int playerid);
    
//   signals:
//     void sig_newDay(int);
    
  private:
    // QTimer calc_data_timer;
    // QTimer calc_ship_movement_timer;
    int m_cycle;
    
  protected:
    virtual void run();
    void produktion(int);
    Wind *m_wind;
    
    QHash<int, Player*> m_Players;
    QHash<int, City*> m_CityHash;
    
    OHParameter m_parameters;
    Player *m_defaultPlayer;
    QQueue<QString> m_messages;
    int m_currentPlayers;
    int m_maxPlayers;
    

};

#endif
