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

#include "position.h"

Position::Position  (const QPoint &coordinates, const QPoint &point, QObject *parent) : 
QObject(parent),
m_point (point),
m_coordinates (coordinates)
{
}

Position::Position(const Position &other) : QObject(other.parent()), m_point (other.m_point), m_coordinates (other.m_coordinates)
{
  
}

/*Position::Position(const QPointF &point, const QPoint &coordinates) : 
m_point (point),
m_coordinates (coordinates)
{
}*/

int &Position::operator[] (char attr)
{
  switch(attr)
  {
    case 'l':
      return m_coordinates.rx();
    case 'p':
      return m_coordinates.ry();
    case 'x':
      return m_point.rx();
    case 'y':
      return m_point.ry();
  }
}


bool operator== ( const Position &pos1, const Position &pos2)
{
  if(pos1.coordinates() == pos2.coordinates() && pos1.point() == pos2.point())
  {
    return true;
  }
  else
    return false;
}

bool operator== ( const Position &pos1, const QPoint &point)
{
  if(pos1.coordinates() == point)
  {
    return true;
  }
  else
    return false;
}

