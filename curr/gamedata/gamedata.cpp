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
 
// #include "kontor.h"
// #include "ship.h"
// #include "wind.h"
// #include "time.h"
// #include "building.h"
// #include "person.h"
// #include "map.h"
// #include "landing.h"
//  #include "factory.h"

#include "gamedata.h"
#include "ohparameter.h"
#include "city.h"

#include <QtDebug>

// #define _DEBUG_CALC_

GameData::GameData(QObject *parent) : QThread(parent), m_wind(new Wind(this)), m_defaultPlayer ( new Player(this)), m_currentPlayers (0), m_maxPlayers(0)
{
//#m_ActiveShip = new Ship(QString());
// m_ActiveShip = 0;
// m_ActiveShip->init();
// m_ActiveCity = 0;
//#m_ActiveKontor = new Kontor();
// m_ActiveKontor = 0;
//#m_ActiveChar = new Person();
// m_ActiveChar = 0;
//#m_CurrentMap = new Map();

// addShip(*m_ActiveShip);
// delete m_ActiveShip;
// m_ActiveShip = &m_ShipList.first();

// m_landingprocess.setStatus(Landing::NotActive);
// connect(&calc_data_timer, SIGNAL(timeout()), this, SLOT(calcData()));
// singleplayer = true;

//#m_anbord = true;


}

// GameData::~GameData()
// {
// 	delete m_ActiveShip;
// 	delete m_ActiveCity;
// 	delete m_ActiveKontor;
// 	delete m_ActiveChar;
//  	m_MapList << *currentMap;
// 	foreach(*currentMap, m_MapList)
// 	{
//  		delete m_CurrentMap;
// 	}
// 	m_MapList.clear();
// 	m_CityList.clear();
// 	m_KontorList.clear();
// }

void GameData::newGame()
{
//   m_difficulty = difficulty;
//   loadDefaultCitys();
//   m_CurrentMap->loadMap("startmap.ohm");
  
}
/*
void GameData::loadDefaultCitys()
{
  m_CurrentMap = new Map();
  QStringList loadmaps;
  loadmaps << "startmap.ohm";

  for(QStringList::iterator i = loadmaps.begin(); i != loadmaps.end(); ++i)
  {
    m_CurrentMap->loadMap(*i);
    if(m_CurrentMap->isCity())
    {
      m_CityList << m_CurrentMap->city();
    }
    if(!loadmaps.contains(m_CurrentMap->mapwest()))
      loadmaps << m_CurrentMap->mapwest();
    if(!loadmaps.contains(m_CurrentMap->mapnorth()))
      loadmaps << m_CurrentMap->mapnorth();
    if(!loadmaps.contains(m_CurrentMap->mapsouth()))
      loadmaps << m_CurrentMap->mapsouth();
    if(!loadmaps.contains(m_CurrentMap->mapeast()))
      loadmaps << m_CurrentMap->mapeast();
  }
}*/


/*
void GameData::addBuilding(const Building &param_building)
{
m_BuildingList << param_building;
}

void GameData::addShip(const ShipData &param_ship)
{
m_ShipList << param_ship;
}

void GameData::addKontor(const Kontor &param_kontor)
{
m_KontorList << param_kontor;
}



void GameData::addPerson(const Person &param_person)
{
m_PersonList << param_person;
}*/

void GameData::addCity(City *param_city)
{
  m_CityHash[param_city->id()] = param_city;
}

void GameData::addPlayer(Player *addedPlayer)
{
  qWarning() << "addPlayer 1";
  m_Players[addedPlayer->id()] = addedPlayer;
  qWarning() << "addPlayer 2";
//   addedPlayer->setParent(this);
  qWarning() << "addPlayer 3";

//   if(addedPlayer->socket() != 0)
//     connect(addedPlayer, SIGNAL(dataAvailable(int)), this, SLOT(loadData(int)));
  qWarning() << "addPlayer 4";
  m_currentPlayers++;
}

void GameData::setMaxPlayers(int count)
{
  m_maxPlayers = count;
}
/*
void GameData::setCurrentPlayers(int count)
{
  m_currentPlayers = count;
}*/



/*void GameData::setCurrentCity()
{
// 	for(QList<CityClass>::iterator it = m_CityList.begin(); it != m_CityList.end(); ++it)
	foreach(m_ActiveCity, m_CityList)
	{
// 		if(it->cityname() == m_CurrentMap->cityname())
		if(m_ActiveCity->name() == m_CurrentMap->city()->name())
		{
// 			m_ActiveCity = &*it;
			break;
		}
	}
}*/


void GameData::run()
{
// calc_ship_movement_timer.start(20);
// connect(&calc_ship_movement_timer, SIGNAL(timeout()), this, SLOT(calcShipMovement()));
exec();
// setPriority(QThread::HighestPriority);
}

/*void GameData::calcShipMovement()
{
#ifdef _DEBUG_CALC_
qWarning() << "void GameData::calcShipMovement()";
#endif
// foreach(shipiterator, ShipList)

// 	for(QList<ShipData>::iterator it = m_ShipList.begin(); it != m_ShipList.end(); ++it)
	foreach(shipiterator, m_ShipList)
	{
		shipiterator->calcPos();
		#ifdef _DEBUG_CALC_
		qWarning() << "Calc ShipMovement: " << shipiterator->name() << shipiterator->id();
		#endif
	}
}*/

/*void GameData::castOff(Ship *newActiveShip)		// ablegen
{
foreach(shipiterator, m_ShipList)
// for(QList<ShipData>::iterator it = m_ShipList.begin(); it != m_ShipList.end(); ++it)
{
	if(shipiterator->id() == newActiveShip->id())
	{
// 		m_ActiveShip = &*it;
		m_ActiveShip = shipiterator;
		shipiterator = 0;
	}
}
emit sig_castOff();
}*/


/*Object* GameData::findObject (int id)
{
  if(m_Objects[id]->id() == id)
  {
    return m_Objects[id];
  }
  else
    return 0;
}*/


/*
// const QVariant &condition,
// 			       Filters filter,
// 			       const QList<Object*> &objectlist)
QList<Object*> GameData::searchObjects(const QList<Object*> &objectlist_a,
					const QPoint &coordinate,
					int objecttype,
					int buildingtype)
{
  QList<Object*> objectlist;
  Object *objectit;
  
  if(objectlist_a.isEmpty())
  {
    objectlist = m_Objects.values();
  }
  else
  {
    objectlist = objectlist_a;
  }
  
  if(!coordinate.isNull())
  {

    foreach(objectit, objectlist)
    {
      if(objectit->coordinates() != coordinate)
      {
	objectlist.removeOne(objectit);
      }
    }
  }
  if(objecttype != -1)
  {
    foreach(objectit, objectlist)
    {
      if(objectit->type() != objecttype)
      {
	objectlist.removeOne(objectit);
      }
    }
  }
  if(buildingtype != -1)
  {
    objectlist = searchObjects(objectlist, QPoint(), Object::BuildingObject);
    if(!objectlist.isEmpty())
    {
      Building *Buildingit;
      foreach(objectit, objectlist)
      {
	Buildingit = dynamic_cast<Building*>(objectit);
	if(Buildingit != 0)
	{
	  if(Buildingit->buildingType() != buildingtype)
	  {
	    objectlist.removeOne(objectit);
	  }
	}
      }
    }
  }

  return objectlist;
  
}
*/

