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

#include "servergamedata.h"
#include "server.h"

#include <networkcommands.h>

#include <QtXml/QXmlStreamWriter>

#include <QFile>

#include <QtDebug>

#include <OMath>
#include <OQString>


#include <QLocalSocket>

ServerGameData::ServerGameData(OHServer *parent) : GameData(parent)
{
  qWarning() << "ServerGameData::ServerGameData(OHServer *parent) : GameData(parent)";
  m_shiptypes.insert(1, ShipType(":/data/schnigge.ohl"));
}

void ServerGameData::createNewGameWorld()
{
  sleep(1);
  QString mapfile(":/img/worldmap.png");
  QList<QPoint> poslist;
  qWarning() << "void ServerGameData::createNewGameWorld(int cityCount)";
  QLocalSocket mapsocket;
  qWarning() << "mapsocket.connectToServer(Localserver::Mapserver);" << Localserver::Mapserver;
  mapsocket.connectToServer(Localserver::Mapserver);
  if(mapsocket.waitForConnected())
  {
//     mapsocket.write(QByteArray::number(cityCount));
    if(mapsocket.waitForReadyRead(120000)) // waits 120 secs;
    {
      int pre_lines  = mapsocket.readLine(99).toInt(); // lines before the Data of the worldmap-image
//       QList<QPoint> pl;
      
      for(int i = pre_lines; i; i--)
      {
	poslist << StringToPoint(mapsocket.readLine(99));
// 	pre_lines--;appQuit
      }
      mapfile = mapsocket.readLine(99);
      
//       if(cityCount > 25)
//       {
// 	cityCount = 25;
//       }
//       for(int i = 0; i<cityCount; i++)
//       {
// 	City *newcity = new City(i, namedb.name());
// 	m_CityHash[i] = newcity;
//       }
    }
    else
    {
      qWarning() << "No Answer!" << mapsocket.error();
    //       delete mapsocket;
    exit();
    return;
    }
  }
  else
  {
    qWarning() << "No Mapserver found. Using default map.";    
    QFile file(":/data/worldmap_citys.ohl");
    file.open(QIODevice::ReadOnly);
    
//     qWarning() << file.readAll();
//     file.reset();
    
    for(int i = 15; i; i--)
    {
      poslist << StringToPoint(file.readLine(99));
      qWarning() << poslist.last();
    }
  }
  
  // create and initialize all citys
  qWarning() << "int i (0)";
  int i (0);
  while(!poslist.isEmpty())
  {
    City *city = new City(m_namedb.name());
    city->init();
    city->setCoordinates(poslist.takeFirst());
    m_CityHash[i] = city;
    i++;
  }
  qWarning() << "Before BROADCASTING MAPFILE";
  
  //send Data to clients
  if(mapfile == ":/img/worldmap.png")
  {
    m_broadcastData = ("worldmap.default");
  }
  else
  {
    QFile file(mapfile);
    file.open(QIODevice::ReadOnly);
    //   m_parent->broadcastData("test");
    m_broadcastData = ("worldmap\n" + file.readAll() + Network::EndOfFile);
  
    file.close();
    qWarning() << "Mapfile broadcasted";
  }
  emit broadcastDataAvailable();
}




void ServerGameData::run()
{
  createNewGameWorld();
  const QHash<int, Player*>::iterator endit = m_Players.end();
  for(QHash<int, Player*>::iterator it = m_Players.begin(); it != endit; ++it)
  {
    initPlayer(*it);
//    m_playerdata.insert(QPair((*it)->id() ,(*it)->properties()));
  }
  exec();
}

void ServerGameData::initPlayer(Player *player)
{
  Ship newship(m_shiptypes.value(1));
  newship.setPosition(Position(m_CityHash.values().at(qrand()%m_CityHash.size())->coordinates()));
  player->addShip(newship);
  m_playerdata.enqueue(qMakePair(player->id(), player->properties()));
  emit sendDataAvailable();
}

QPair<int, QByteArray> ServerGameData::dequeueData()
{
  return m_playerdata.dequeue();
}


void ServerGameData::playerReady(int id)
{
  player(id)->setReady(true);
//   if(m_Players.size() > 1)
  {
    Player *player;
    int readycount(0);
    foreach(player, m_Players)
    {
      if(player->ready())
	readycount++;
    }
    qWarning () << "void ServerGameData::playerReady(int id)" << readycount << m_Players.size();
    if(readycount == m_Players.size())
      start();
  }
}

/*QByteArray ServerGameData::broadcastData() const
{
  emit 
  return m_broadcastData;
}*/

void ServerGameData::calcData()
{
  #ifdef _DEBUG_CALC_
  qWarning() << "GameData::calcData()";
  #endif
  
  m_wind->refresh();
  /*
	if(m_GameTime.refreshTime())			//returns true, when a new day starts ...
	{
		qWarning() << "A new day is rising up ... :-)";
// 		emit sig_newDay(cycle);
		produktion(m_cycle);
		if(m_cycle > 2000000000)	// 2 000 000 000
		{
			m_cycle = 0;
		}
	}

// 	for(QList<ShipData*>::iterator it = m_ShipList.begin(); it != m_ShipList.end(); ++it)
 	foreach(shipiterator, m_ShipList)
	{
		shipiterator->calcMovement(m_wind.v(), m_wind.dir());
	}
	shipiterator = 0;*/
}

/*void ServerGameData::addPlayer(Player *addedPlayer)
{
  GameData::addPlayer(addedPlayer);*/
/*  m_Players[addedPlayer->id()] = addedPlayer;
  addedPlayer->setParent(this);
  if(addedPlayer->socket() != 0)
    connect(addedPlayer, SIGNAL(dataAvailable(QByteArray*)), this, SLOT(loadData(QByteArray*)));
  m_currentPlayers++;*/
//   connect(addedPlayer, SIGNAL(playerlistRequested(int)), this, SLOT(broadcastPlayerlist()));
//   connect(addedPlayer, SIGNAL(disconnected(int)), this, SLOT(finishPlayer(int)));
//}


QByteArray ServerGameData::playerXmlList() const
{
  qWarning() << "QByteArray ServerGameData::playerXmlList() const";
  QByteArray data;
  QXmlStreamWriter writer(&data);
  const QHash<int, Player *>::const_iterator endit = m_Players.end();
  
  writer.writeStartElement("playerlist");
  writer.writeAttribute("cur", QString::number(m_parent->currentPlayers()));
  writer.writeAttribute("max", QString::number(m_parent->maxPlayers()));
  
  for(QHash<int, Player *>::const_iterator it = m_Players.begin(); it != endit; ++it)
  {
    writer.writeEmptyElement("player");
    writer.writeAttributes((*it)->xmlAttributes());
  }
  writer.writeEndDocument();
  return data;

}

// void ServerGameData::broadcastPlayerlist()
// {
//   broadcastData(playerXmlList());
// }



/*void ServerGameData::startTimer()
{
// calc_data_timer.start(const_calc_data_delay);
// if(singleplayer)
{
start(QThread::HighestPriority);
}
}



void ServerGameData::stopTimer()
{
qWarning() << "void GameData::pause()";
// calc_data_timer.stop();
// calc_ship_movement_timer.stop();
quit();
}*/

void ServerGameData::finishPlayer(int pid)
{
  qWarning() << "void ServerGameData::finishPlayer(int pid)";
  Player *oldplayer = m_Players.take(pid);
  QString fn = QString::number(oldplayer->id()) + ".ohp";
  QFile file(fn);
  file.open(QIODevice::WriteOnly);
  file.write(oldplayer->properties());
  file.close();
  qWarning() << "Before deleting player.";
  
  delete oldplayer;
  qWarning() << "After deleting player.";
}
