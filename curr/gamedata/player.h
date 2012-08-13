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

#ifndef _Player_H
#define _Player_H

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QList>
// #include <QtCore/QTimer>
// #include <QtCore/QTime>


#include "kontor.h"
#include "ship.h"
#include <Building>

class QXmlStreamAttributes;



class Player : public QObject
{
  Q_OBJECT
  public:
    Player(QObject *parent = 0);
    Player(const QString &, QObject *parent = 0);
//     Player(const Player &);
//     Player &operator=(const Player &p1);
//     ~Player();
    
/*    enum control
    {
      human = 0,
      bot = 1
    };*/
    
    enum gamestate
    {
      WaitForReady = 0x010,
      Ready = 0x011,
      Playing = 0x012,
      Finished = 0x013
    };
    
    
    

    int id		()	const	{	return m_id;		}
    int ping		()	const	{	return m_ping;		}
    bool ready		()	const	{	return m_ready;		}
    
    QString name	()	const	{	return m_name;		}
//     QString lastName	()	const	{	return m_lastName;	}
    
//     control controling();
    
    void setPID (int newID = 0);
    void setPing	(int msecs);    
    void setReady	(bool);
    void setName	(const QString &);
//     void setLastName	(const QString &);
    void addShip(Ship &);
    
    QXmlStreamAttributes xmlAttributes() const;
    //     void setXmlAttributes(const QXmlStreamAttributes &);
    
    
    QByteArray properties() const;
    Ship *currentShip () { return m_currentShip; }
    void setCurrentShip(int);
    
    
    
  protected:
    static int m_idcounter;
    int m_id;
    
    QString m_name;
//     QString m_lastName;
    
    QHash<int, Ship> m_ships;
    Ship *m_currentShip;
    QHash<int, Building*> m_buildings;
    QHash<int, Kontor> m_kontore;
    int m_ping;
    bool m_ready;
};

#endif
