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

#ifndef _Position_H
#define _Position_H

#include <QtCore/QPointF>
#include <QtCore/QObject>


class Position : public QObject
{
  Q_OBJECT
  public:
    
    Position(const QPoint &coordinates = QPoint(0,0), const QPoint &point = QPoint(0,0), QObject * = 0);
    Position(const Position &);
//     Position(const QPointF &point = QPointF(0,0), const QPoint &coordinates = QPoint(0,0) );
/* Position(const Position &other) :
    m_id (other.m_id),
    m_point (other.m_point),
    m_coordinates (other.m_coordinates)
  {
  }*/


void operator= (const Position &other)
{
  m_coordinates = other.m_coordinates;
  m_point = other.m_point;
}

bool operator== ( const Position &other) const
{
  if(other.m_coordinates == m_coordinates && other.m_point == m_point)
  {
    return true;
  }
  else
    return false;
}

int &operator[] (char attr);



void setPoint	(const QPoint &point)		{	m_point = point;	}
void setCoordinates (const QPoint &point)	{	m_coordinates = point;	}

const QPoint	&coordinates	() const	{	return m_coordinates;	}
const QPoint	&point		() const	{	return m_point;		}


private:
  QPoint m_point;
  QPoint m_coordinates;
  
protected:
//   int x; //x-coordinate on map
//   int y; //y-coordinate on map
  
//   int l; //longitude (lambda) - geogr. laenge
//   int p; //latitude (phi) - geogr. breite
  
};

bool operator== ( const Position &pos1, const Position &pos2);
bool operator== ( const Position &pos, const QPoint &point);


#endif
