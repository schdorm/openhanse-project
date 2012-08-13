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
#ifndef _SHIPDATA_H
#define _SHIPDATA_H


#include <QtCore/QObject>
#include <QtCore/QTimer>

#include "position.h"
#include <Goods>

#define _SIMPLE_SHIP_CONTROL

class QXmlStreamAttributes;
class ShipType;

// for clean xml-communication with server ; save/load gamedata

class Ship //: public QObject
{
//   Q_OBJECT
  public:
    Ship();
    Ship(const Ship &);
    Ship(const ShipType &, const QString & = 0);
    ~Ship();

    
    int	id			() const	{	return m_id;				}
    const Position &position	() const	{	return m_position;			}
    Position &position		()		{	return m_position;			}
    const QPoint &coordinates	() const	{	return m_position.coordinates();	}
    QString printPosition() const;
    
    int ownerID			() const	{	return m_ownerid;			}
    void setName		(const QString &);
    const QString &name		() const	{	return m_name;				}
    int type			() const	{	return m_type;				}
    float v			() const	{	return m_v;			}
    float settedSailSurface	() const	{	return m_settedSailSurface;	}
    float toSettedSailSurface	() const	{	return m_toSettedSailSurface;	}
    
    #ifndef _SIMPLE_SHIP_CONTROL
    float sailDir		() const	{	return m_sailDir;		}
    
    float rudderDir		() const	{	return m_rudderDir;		}
    float toRudderDir		() const	{	return m_toRudderDir;		}
    
    #endif
    
    float dir			() const	{	return m_dir;			}
    float toDir			() const	{	return m_toDir;			}
    
    
    const Goods &goods		() const	{	return m_cargo;			}
    const Goods &cargo		() const	{	return m_cargo;			}
    // const Position &currentPosition() const {return m_currentPosition;		}
    
    int condition		() const	{	return m_condition;		}
    int controlcondition	() const	{	return m_controlCondition;	}
    int seamen			() const 	{	return m_seamen;		}
    
    bool anchored		() const	{	return m_anchored;		}
    
    // void bewegungsbeschreibung() --> calculate movement-things ...
    void calcMovement		(int, const float &);
    
    // control: set - fct.
    void set_ToSettedSailSurface(float);
    void setDirToPoint(const QPointF &point);
    
    #ifndef _SIMPLE_SHIP_CONTROL
    void set_SailDir		(float);
    void set_ToRudderDir	(float);
    #endif
    
    void setOwnerID		(int ownerID);
    bool setCargo		(const Goods &);
    
    void brake			(const float &);
    void anchor			();
    
    void setSeamen		(int);
    
    void setControlDifficulty	(int);
    
    
    void setPosition		(const Position &);
    QXmlStreamAttributes characteristics() const;
    void setNavCharacteristics(const QXmlStreamAttributes &);
    
    void setState(const QXmlStreamAttributes &);
    QXmlStreamAttributes state() const;
    
    int & operator[] (int goodkey)
    {
      return m_cargo[goodkey];
    }
    
    int operator[] (int goodkey) const
    {
      return m_cargo[goodkey];
    }
    
    void operator=(const Ship &other);
    
//     void setRefreshRate(int);
//     static void setGameSpeed(int);
    
//   public slots:
    void calcPos();
	
//   signals:
//     void navChanged(); // is emitted, when the player sets another direction or changes the sail surface
    
  private:
//     int m_delayvar;
//     int m_ControlDifficulty;
    // bool m_MouseControl;
    //    Landing m_landingprocess;
    static int m_idcounter;
    
//     static int gamespeed;		// gamespeed in percent
    
//     int m_posCalcDelay;		// calc pos, dir
//     int m_navCalcDelay; 		// calc sails, v
//     QTimer m_refreshTimer;
    
  protected:
    int m_id;
    int m_type;
    int m_ownerid;
    QString m_name;				// the ships name
    // UI6L
    int m_condition;			// Zustand allgemein ...
    int m_controlCondition;		// Manoevrierzustand: wie gut kann das Schiff lenken, wie intakt sind die Segel
    int m_seamen;			// Matrosen
    
    Goods m_cargo;			//Ladung
    int m_mass;
    
    Position m_position;
    
    float m_v;
    
    float m_dir;
    float m_toDir;	// mouse-control
    
//     float m_controlVelocity;		//describes, how fast a ship can turn; drops, if the ship is spoilt / damaged ..
    float m_settedSailSurface;
    float m_toSettedSailSurface;
    float m_maxSailSurface;
    
    
    #ifndef _SIMPLE_SHIP_CONTROL
    float m_rudderDir;		//keyboard-control
    float m_toRudderDir;	// 	''
    
    // control-difficulty +
    float m_sailDir;
    #endif
    
    bool m_anchored;
};

Ship loadShip(const QXmlStreamAttributes &);

#endif
