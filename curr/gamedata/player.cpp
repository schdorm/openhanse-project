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

#include "player.h"
// #include <QtNetwork/QTcpSocket>
#include <QtXml/QXmlStreamAttributes>
// #include <OMath>


#define DEBUG_PLAYER
#ifdef DEBUG_PLAYER
#include <QtDebug>
#endif

int Player::m_idcounter = 0;

/*Player::Player(QTcpSocket *socket, QObject *parent) : QObject(parent), m_id(m_idcounter), m_socket(socket), m_pingTimer(new QTimer)
{
  qWarning()<< "Player::Player( QObject *parent, QTcpSocket *socket)";
  m_idcounter++;
  if(socket == 0)
    m_controling = bot;
  else
  {

    m_controling = human;
    m_socket->setParent(this);
    setPingIntervall(pingintervall);
    connect(m_pingTimer, SIGNAL(timeout()), this, SLOT(sendPingRequest()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(handleSocketData()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(m_socket, SIGNAL(disconnected()), m_pingTimer, SLOT(stop()));
//     connect(m_socket, SIGNAL(error( QAbstractSocket::SocketError)), this, SLOT(pES()));
  }
  qWarning() << "New Player created:" << m_id;
}*/

Player::Player(QObject *parent) : QObject(parent), m_id(m_idcounter),  m_currentShip (0), m_ready (false)
{
  m_idcounter++;
}

Player::Player(const QString &name, QObject *parent) : QObject(parent), m_id(m_idcounter), m_name(name), m_currentShip (0), m_ready (false)
{
  m_idcounter++;
}

/*void Player::setEnabled(bool enable)
{
  m_enabled = enable;
  if(enable)
  {
    if(m_socket != 0)
    {
      if(m_socket->state() == QAbstractSocket::ConnectedState)
      {
	setPingIntervall(pingintervall);
	connect(m_pingTimer, SIGNAL(timeout()), this, SLOT(sendPingRequest()));
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(handleSocketData()));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
	connect(m_socket, SIGNAL(disconnected()), m_pingTimer, SLOT(stop()));
      }
    }
  }
  else
  {
    if(m_socket != 0)
    {
      m_socket->disconnectFromHost();
    }
  }
}*/

/*void Player::pES()
{
  qWarning() << m_socket->errorString();
}*/

// Player::Player(QObject *parent) : QObject(parent), m_id(m_idcounter), m_socket(0), m_pingTimer(0)
// {
//   m_idcounter++;
// }


// Player::Player() : m_id(m_idcounter), m_socket(0)
// {
//   m_idcounter++;
//   m_controling = bot;
// }

/*Player::Player(const Player &p1) m_firstName (p1.m_firstName), m_lastName (p1.m_lastName), m_id (p1.m_id),  m_socket (p1.m_socket), 
  m_controling (p1.m_controling),
  m_ships = p1.m_ships;
  m_currentShip = p1.m_currentShip;
  m_Buildings = p1.m_Buildings;
  m_Kontore = p1.m_Kontore;  
{
  m_socket->setParent(this);
}*/


/*
Player::~Player()
{
//   if(m_socket != 0)
//    {
//      delete m_socket;
//    }
}*/


/*Player & Player::operator=(const Player &p1)
{
  m_firstName = p1.m_firstName;
  m_lastName = p1.m_lastName;
  m_id = p1.m_id;
  m_socket = p1.m_socket;
  m_socket->setParent(this);
  m_controling = p1.m_controling;
  m_ships = p1.m_ships;
  m_currentShip = p1.m_currentShip;
  m_Buildings = p1.m_Buildings;
  m_Kontore = p1.m_Kontore;  
}*/
/*Player::control Player::controling()
{
  return m_controling;
}*/

void Player::setPID(int newID)
{
  if(newID != 0)
    m_id = newID;
}

void Player::setReady(bool ready)
{
  m_ready = ready;
}

void Player::setName(const QString &name)
{
  m_name = name;
}

// void Player::setLastName(const QString &lastName)
// {
//   m_lastName = lastName;
// }

QXmlStreamAttributes Player::xmlAttributes() const
{
  QXmlStreamAttributes result;
  result.append("id", QString::number(m_id));
  result.append("ping", QString::number(m_ping));
  result.append("name", m_name);
//   result.append("lastName", m_lastName);
  return result;
}

void Player::addShip(Ship &newship)
{
  newship.setOwnerID(m_id);
  m_ships.insert(newship.id(), newship);
}


/*void Player::sendData(const QByteArray &data)
{
  #ifdef DEBUG_PLAYER
  qWarning() << "void Player::sendData(const QByteArray &data)\n" << data;
  #endif
  if(m_socket != 0)
    if(m_socket->isValid())
    {
      m_socket->write(data);
      qWarning() << "Data successfull sent!";
    }
}*/

void Player::setPing (int msecs)
{
  m_ping = msecs;
}

QByteArray Player::properties() const
{
  QByteArray f_properties;
  QXmlStreamWriter writer(&f_properties);
  writer.writeStartElement("player");
  writer.writeAttributes(xmlAttributes());
  const QHash<int, Ship>::const_iterator endits = m_ships.end();		//enditerator ships

  for(  QHash<int, Ship>::const_iterator its = m_ships.begin(); its != endits; ++its)	// iterator ships
  {
    writer.writeStartElement("ship");
    writer.writeEmptyElement("state");
    writer.writeAttributes(its->state());
    writer.writeEmptyElement("nav");
    writer.writeAttributes(its->characteristics());
    writer.writeEmptyElement("goods");
    writer.writeAttributes(its->cargo().xmlAttributes());
    writer.writeEndElement();
    
  }
  
  const QHash<int, Building*>::const_iterator enditb = m_buildings.end();	//enditerator buildings
  for(	QHash<int, Building*>::const_iterator itb = m_buildings.begin(); itb != enditb; ++itb)	// iterator ships
  {
    writer.writeStartElement("building");
    writer.writeEndElement();
    
  }
  writer.writeEndDocument();
  return f_properties;
}

void Player::setCurrentShip(int id)
{
  if(m_ships.contains(id))
    m_currentShip = &m_ships[id];
  else
    m_currentShip = 0;
}
