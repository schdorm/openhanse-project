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
#ifndef _BUILDING_H
#define _BUILDING_H


#include <QtCore/QByteArray>
#include <QtCore/QRect>

class QXmlStreamAttributes;

class Building 		//Gebaudeklasse
{
  public:
    enum Types
    {
      null = 0,
      Wall = 4001,
      Gate = 4002,
      Tower = 4020,
      
      Kontor = 4100,
      StorageArea = 4102,
      Warehouse = 4105,
      Tent = 4201,
      Hut = 4204,
      WorkerHouse = 4210,
      CitizenHouse = WorkerHouse + 2,
      WealthyHouse = CitizenHouse + 2,
      Factory = 4300,			// Werkstaetten - workshops
      
      Market = 4900,
      Port = 4902,
      Townhall = 4904,
      Church  = 4905,
      Bank = 4906,
      Tavern = 4907,

//       namespacexyz,
      Buildinglot = 0xFFFF			// Baustelle
    };
    
    int	id		()	const	{	return m_id;	}
    int buildingType	()	const	{	return m_type;	}
    int people		()	const 	{	return m_people;}
    int state		()	const	{	return m_state; }
    QRect &pos		()		{	return m_pos;	}
    const QRect &pos	()	const	{	return m_pos;	}
    int ownerID		()	const	{	return m_ownerid;}
    
    void setPeople	(int);
    void setPos		(const QRect &);
    void setState	(int a_state);
    void setOwnerID	(int);
    
//     virtual QByteArray description() const = 0;
    
    virtual QXmlStreamAttributes xmlAttributes() const;
//     virtual void setXmlAttributes(const QXmlStreamAttributes &);
    
  protected:
    Building(int type = null);
    
    int m_id;
    int m_type;
    
    int m_people;
    int m_state;
    
    int m_ownerid; // -1 -> owner = city; else the ownerid = playerid;
    
    QRect m_pos;
};

#ifdef buildingcast
#include <typeinfo>

template<class T>
T building_cast(Building *a_building)
{
  if(a_building != 0)
  {
    if(typeid(T) == typeid((*a_building)))
    {
      return dynamic_cast<T> (a_building);
    }
  }
  return 0;
}
#endif

#endif
