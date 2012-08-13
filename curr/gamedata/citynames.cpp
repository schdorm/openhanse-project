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

#include "citynames.h"

#include <QtCore/QFile>
#include <QtDebug>

CityNameDB::CityNameDB()
{
  qWarning() << "CityNameDB::CityNameDB()";
  QFile file(":/data/citylist.ohl");
  if(file.open(QIODevice::ReadOnly))
  {
    while(!file.atEnd())
    {
      m_citynames << QString(file.readLine()).trimmed();
      qWarning() << m_citynames.size() << m_citynames.last();
    }
  }
  else
  {
    qWarning() << "Could not open Citynamelib!";
  }
}

QString CityNameDB::name()
{
  qWarning() << "QString CityNameDB::name()";
  int index = qrand() % m_citynames.size();
  qWarning() << "Index: " << index << m_citynames.size() << "Name:" << m_citynames.value(index);;
  return m_citynames.takeAt(index);
//   return 0;
}
