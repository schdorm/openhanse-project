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

#include "data/building.h"
#include <QtCore/QXmlStreamAttributes>
#include "libs/oqstring.h"

Building::Building(int a_type) : m_type (a_type), m_ownerid(-1)
{
  static int idcounter;
  m_id = idcounter;
  idcounter++;
  m_state = 0;
}

void Building::setPeople(int people)
{
  m_people = people;
}

void Building::setState(int a_state)
{
  m_state = a_state; 
}

void Building::setPos(const QRect &point)
{
  m_pos = point;
}

void Building::setOwnerID(int oid)
{
  m_ownerid = oid;
}

QXmlStreamAttributes Building::xmlAttributes() const
{
  QXmlStreamAttributes attr;
  attr << QXmlStreamAttribute("id",	QString::number(m_id));
  attr << QXmlStreamAttribute("people",	QString::number(m_people));
  attr << QXmlStreamAttribute("state",	QString::number(m_state));
  attr << QXmlStreamAttribute("owner",	QString::number(m_ownerid));
  attr << QXmlStreamAttribute("pos",	StringFromPoint(m_pos.topLeft()));
  attr << QXmlStreamAttribute("size",	StringFromSize(m_pos.size()));
  
  return attr;
}

/*QByteArray Building::description() const
{
  return "";
}*/