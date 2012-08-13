/***************************************************************************
 *   Copyright (C) 2009  - 2010 by Christian Doerffel                      *
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

#include "gamedata.h"

#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamAttributes>

#include <QtDebug>

#include <QFile>

int idOf(const QXmlStreamAttributes &attributes);

// void GameData::loadData(int playerid)
// {
//   loadData(player(playerid)->bufferedData());
// }

void GameData::loadData(const QByteArray &data)
{
  qWarning() << "void GameData::loadData(const QByteArray &data): " << data;
  QXmlStreamReader reader(data);
  
  bool playerToken;
  int currentMainID = 0;		// Ownerid: Player or City
  int currentSubID = 0;			// Objectid: Ship, Building, Person, etc.
  enum Object
  {
    Ship,
    Building,
    Person
  } currentObject;
  bool parse_EOF = false;
  
  while(!parse_EOF)
  {
    switch(reader.readNext())
    {
      case QXmlStreamReader::StartElement:
      {
	qWarning() << "StartElement: " << reader.name();
	if(reader.name() == "ship")
	{
	  currentObject = Ship;
	  currentSubID = idOf(reader.attributes());
	}
	else if(reader.name() == "player")
	{
	  playerToken = true;
	  currentMainID = idOf(reader.attributes());
	  if(!playerExists(currentMainID))
	  {
	    qWarning() << "New Player required:" << currentMainID;
	    Player *f_player = new Player(this);
	    f_player->setPID(currentMainID);
// 	    f_player->setPing(reader.attributes().value("ping").
	    f_player->setName(reader.attributes().value("name").toString());
// 	    f_player->setLastName(reader.attributes().value("lastName").toString());
	    addPlayer(f_player);
	  }
	  m_Players.value(currentMainID)->setPing(reader.attributes().value("ping").toString().toInt());
	  
	}
	else if(reader.name() == "city")
	{
	  playerToken = false;
	  currentMainID = idOf(reader.attributes());
	}
	else if(reader.name() == "playerlist")
	{
	  m_maxPlayers = reader.attributes().value("max").toString().toInt();
	  m_currentPlayers = reader.attributes().value("cur").toString().toInt();
	}
	else if(reader.name() == "wind")
	{
	  m_wind->setV(reader.attributes().value("v").toString().toDouble());
	  m_wind->setV(reader.attributes().value("dir").toString().toDouble());
	}
/*	else if(reader.name() == "worldmap")
	{
	  if(reader.readNext() == QXmlStreamReader::Characters)
	  {
	    m_worldmapdata = reader.text().toString().toUtf8();
	    QFile file("wm1.png");
	    file.open(QIODevice::WriteOnly);
	    file.write(data);
	    file.close();
	    emit worldmapReceived();
	  }
	}*/
	break;
      }
      case QXmlStreamReader::EndElement:
      {
	qWarning() << "case QXmlStreamReader::EndElement:" << reader.name();
	parse_EOF = reader.atEnd();
	break;
      }
      case QXmlStreamReader::Invalid:
      {
	qWarning() << "case QXmlStreamReader::Invalid:" << reader.errorString();
	parse_EOF = true;
	break;
      }
      default:
      {
	parse_EOF = reader.atEnd();
	break;
      }
    }
  }
  qWarning() << "Finished loading";
}

void GameData::loadItems(QXmlStreamReader *reader, int ownerid, bool isPlayer)
{
  bool inside(true);
  while(inside)
  {
    switch(reader->readNext())
    {
      case QXmlStreamReader::StartElement:
      {
	if(reader->name() == "building")
	{
	  if(isPlayer)
	  {
	  }
	  else
	  {
	  }
	}
	else if(reader->name() == "ship")
	{
	  Ship a = loadShip(reader->attributes());
	  m_Players.value(ownerid)->addShip(a);
	}
	break;
      }
      case QXmlStreamReader::EndElement:
      {
	inside = reader->name() == "city" | reader->name() == "player" | reader->atEnd();
	break;
      }
      case QXmlStreamReader::Invalid:
      {
	qWarning() << "Error: " << reader->error() << reader->errorString();
      }
      default:
	break;
    }
  }
}

int idOf(const QXmlStreamAttributes &attributes)
{
  return attributes.value("id").toString().toInt();
  /*  if(attributes.hasAttribute("id"))
  {
//     return
  }
  else return -1;*/
}
