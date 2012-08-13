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

#ifndef _AbstractMap_H
#define _AbstractMap_H

class AbstractCity;
#include "data/abstractmapobject.h"

#include <QtCore/QList>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtCore/QHash>




class AbstractMap
{
  public:
    AbstractMap();
    //     Map(const Map &);
//     AbstractMap(const AbstractMap *);		// Pointer - Copy-Constructor
    //     ~Map();
    

    enum Type
    {
      Sea	= 10000,
      Coast	= 10001,
      Land	= 10002,
      Citymap	= 10100
    };
    
    enum Orientations
    {
      null	= 0,
      North	= 128,
      East	= 129,
      South	= 130,
      West	= 132
    };
    
    bool load(const QString &);
    
    
    // const City *ccity()	const	{	return m_city;		}
    bool isCity	()	const;
    
    // {	return (m_type == Map::Coast ^ Map::Citymap || m2type == Map::Land ^ Map::Citymap);	}
    // City city() const;
    // City city	()	const	{	return m_city;			}
    AbstractCity *city	()		{	return m_city;			}
    const AbstractCity *city()	const	{	return m_city;			}
    
    
    AbstractCity *cityinstance();

    void setCity(const AbstractCity &newCity);
    // const QString &cityname()	const	{	return m_cityname;	}
    
    
    void addObject				(const AbstractMapObject *a_newAMO = 0);
    void removeObject				(int);
    
    QList <AbstractMapObject> objects 		() const	{	return m_Objects.values();	}
    AbstractMapObject * object			(int a_id)	{	return &m_Objects[a_id];	}
    AbstractMapObject object			(int a_id) const{	return m_Objects.value(a_id);	}
    
    //     const MapObject *object		(int a_id) const{	return &m_Objects[a_id];	}
    //     QList <MapObject> *objects ()		{	return &m_ObjectList;	}
    //     const QList <MapObject> &objectList	() const	{	return m_ObjectLists		}
    
    
    QString filename 	()	const	{	return m_filename;	}
    QString name	() 	const 	{	return m_name;		}
    QPoint coordinates	()	const	{	return m_coordinates;	}
    QSize size		()	const	{	return m_size;		}
    QString background	()	const	{	return m_background;	}
    
    QString mapnorth	()	const	{	return m_mapnorth;	}
    QString mapeast	()	const	{	return m_mapeast;	}
    QString mapsouth	()	const	{	return m_mapsouth;	}
    QString mapwest	()	const	{	return m_mapwest;	} 
    
    int type		()	const	{	return m_type;		}
    
    
    void setCoordinates	(const QPoint &);
    void setSize		(const QSize &);
    void setBackground	(const QString &);
    void setName(const QString&);
    
    void setMapnorth	(const QString &);
    void setMapsouth	(const QString &);
    void setMapwest		(const QString &);
    void setMapeast		(const QString &);
    void setType	(int);
    
  private:
    // static int mapcounter;
    
    // QString m_mapdirectory;
    
  protected:
    quint32 m_id;
    QString m_filename;
    QString m_name;
    QPoint m_coordinates;
    QSize m_size;
    QString m_background;
    QString m_mapnorth;
    QString m_mapeast;
    QString m_mapsouth;
    QString m_mapwest;
    int m_type;
    AbstractCity *m_city;
    
//     QList <AbstractMapObject> m_ObjectList;
    QHash <int, AbstractMapObject> m_Objects;
    
};

AbstractMap &operator<=(AbstractMap &m1, const AbstractMap &m2);

#endif
