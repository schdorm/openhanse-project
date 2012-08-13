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
class Player;
class OHServer;

#include <GameData>
#include <citynames.h>
#include <shiptype.h>

#ifndef _ServerGameData_H
#define _ServerGameData_H

class ServerGameData : public GameData
{
  Q_OBJECT
  public:
    ServerGameData(OHServer *parent = 0);
    void createNewGameWorld();
    void calcData();
    
//     void addPlayer(Player*);
    QByteArray broadcastData()	const { return m_broadcastData; }
    
    QByteArray playerXmlList() const;
    
    void finishPlayer(int);
    void initPlayer(Player *);
    
    QPair<int, QByteArray> dequeueData();
  public slots:
    void playerReady(int);
//     void broadcastPlayerlist();
    
  signals:
//     void broadcastData
    void broadcastDataAvailable();
    void sendDataAvailable();
    
  private:
    CityNameDB m_namedb;
    OHServer *m_parent;
    QByteArray m_broadcastData;
    
    QHash<int, ShipType> m_shiptypes;
    QQueue <QPair<int, QByteArray> > m_playerdata;
  protected:
    void run();
};

#endif
