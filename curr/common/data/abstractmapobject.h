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

#ifndef _MAPOBJECT_H
#define _MAPOBJECT_H

#include <QtCore/QPoint>
#include <QtCore/QString>

class AbstractMap;

class AbstractMapObject
{
  public:
    AbstractMapObject(int a_role, const QString &a_filename, const QPoint &a_position, const QString &a_name, const QString &a_tooltip, double a_zvalue, AbstractMap *a_parent = 0);
    
    AbstractMapObject(AbstractMap *a_parent = 0);
    
    enum 
    {
      Water = 6000,
      Land = 6001,
      Mapdecoration = 6002
    };
    
    enum GraphicType
    {
      SVG = 0x05,
      Brush = 0x0B,
      Image = 0x01
    };
    
    
    
    int 	id	 () const	{	return m_id;			}
    int		role 	 () const	{	return m_role;			}
    QString	filename () const	{	return m_filename;		}
    QString	imagepath() const	{	return m_filename;		}
    GraphicType graphicType () const	{	return m_graphicType;		}
    QString	tooltip  () const	{	return m_tooltip;		}
    QString	name	 () const	{	return m_name;			}
    QPoint	position () const	{	return m_position.toPoint();	}
    QPointF	positionF() const	{	return m_position;		}
    double	zValue	 () const	{	return m_zValue;		}
    AbstractMap *parent	 () const	{	return m_parent;		}
    
    void setRole 	(int);
    void setFilename	(const QString& );
    void setImagepath	(const QString& );
    void setGraphicType (GraphicType);
    void setTooltip	(const QString& );
    void setName	( const QString&);
    void setPosition	(const QPointF & );
    void moveBy		(qreal, qreal);
    void setZValue	(double);
    
    
//     void operator=(const MapObject &other);

  private:
    int m_id;
    int m_role;

    QString m_filename;
    QPointF m_position;
    QString m_name;
    QString m_tooltip;
    GraphicType m_graphicType;
    
    double m_zValue;
    static int M_IDCounter;
    
    AbstractMap *m_parent;
};

bool operator==(const AbstractMapObject &m1, const AbstractMapObject &m2);

#endif
