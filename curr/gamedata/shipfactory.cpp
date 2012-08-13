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

#include <OHSettingsDir>

#include <QStringList>
#include <QFile>

#include "shipfactory.h"
#include "player.h"

QString ShipFactory::typeName(int type)
{
  return m_shipnames.value(type);
}

void ShipFactory::readShipLib()
{
  QStringList paths;
  QFile file(settingsdir().append("shiplib.ohl"));
  file.open(QIODevice::ReadOnly);
  while(!file.atEnd())
  {
    paths << file.readLine();
  }
  file.close();
}

Ship *ShipFactory::createShip(Player *, int type, const QString &name)
{
  if(name == 0)
  {
    m_name = m_shipnames.value(type);
  }
  Ship *createdShip = new Ship();
  return createdShip;
}