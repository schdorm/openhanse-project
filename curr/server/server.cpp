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

#include <OMath>

#include "server.h"
#include "serversocket.h"

#include <networkcommands.h>

// #include <QtXml/QXmlStreamWriter>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

#include <QtCore/QCryptographicHash>
#include <QtCore/QXmlStreamReader>

#include <QtCore/QCoreApplication>

#include <QtDebug>

#include "servergamedata.h"

// #include <QtCore/QMutex>

OHServer::OHServer(QObject *parent) : QTcpServer(parent), m_admServer(new QLocalServer), m_admSocket(0), m_nameBroadcaster(0), m_GameData(new ServerGameData(this)), m_pingTimer(new QTimer(this)), m_maxPlayers(8), m_currentPlayers(0)//, mutex(new QMutex)
{
  qWarning() << "OHServer::OHServer(QObject *parent) : ";
  m_GameData->setMaxPlayers(m_maxPlayers);
  m_pingTimer->start(2000);
  m_admServer->removeServer(Localserver::Name);
  m_admServer->setMaxPendingConnections(1);
//   enableAdmServer();
//   connect(m_admServer, SIGNAL(newConnection()), this, SLOT(handleAdmConnection()));
  
  connect(m_GameData, SIGNAL(broadcastDataAvailable()), this, SLOT(broadcastGameData()));
  connect(m_GameData, SIGNAL(sendDataAvailable()), this, SLOT(sendData()));
}

// QAbstractSocket::AddressInUseError


void OHServer::ohlisten(const QString &serverPassword)
{
  qWarning() << "void OHServer::ohlisten(QString spw)" << serverPassword;
  m_serverAdminPassword = serverPassword.toUtf8();
  if(!isListening())
  {
    qWarning() << m_currentPlayers << m_maxPlayers;
    if(m_currentPlayers < m_maxPlayers)
    {
      if(!listen(QHostAddress::Any, 9967))
	qWarning() << "Error while server trys to \"listen\"!";
      else
	qWarning() << "Server ready";
    }
    else 
      qWarning() << "ohlisten: too many players, listening aborted";
  }
//   connect(this, SIGNAL(newConnection()), this, SLOT(newPlayer()));
}

void OHServer::handleAdmConnection()
{
  qWarning() << "void OHServer::handleAdmConnection()";
  if(m_admServer->hasPendingConnections())
  {
    m_admState = New;
    m_admSocket = m_admServer->nextPendingConnection();
    m_admServer->close();
    m_admTimer = new QTimer(m_admSocket);
    m_admTimer->start(40000);
    connect(m_admTimer, SIGNAL(timeout()), this, SLOT(enableAdmServer()));
    connect(m_admSocket, SIGNAL(disconnected()), this, SLOT(enableAdmServer()));
    connect(m_admSocket, SIGNAL(readyRead()), this, SLOT(handleData()));
  }
}

void OHServer::enableAdmServer()
{
  qWarning() << "void OHServer::enableAdmServer()";
  if(m_admSocket != 0)
  {
    m_admState = null;
    if(m_admSocket->state() == QLocalSocket::ConnectedState)
      m_admSocket->close();
    m_admSocket->deleteLater();
    m_admSocket = 0;
    m_admTimer = 0;
  }
  m_admServer->listen(Localserver::Name);
  qWarning() << m_admServer->errorString();
}

void OHServer::handleData(int connection)
{
  // if(data.startsWith("<") --> load; else --> rest ...
  QByteArray *data(0);
  AdmStates state (null);
//   QIODevice *device (0);
  switch(connection)
  {
    case -1: // is Adm-Connection
    {
      data = new QByteArray(m_admSocket->readAll());
      state = m_admState;
//       device = m_admSocket;
      break;
    }
    default: // player conn
    {
      ServerSocket *socket = m_sockets.value(connection);
      if(socket != 0)
      {
	data = new QByteArray(socket->bufferedData());
// 	data = new QByteArray(socket->readAll());
// 	device = socket;
	if(socket->isAdmin())
	{
	  state = Admin;
	}
	else
	  state = User;
      }
      break;
    }
  }
//   if(device == 0)
//   {
//     qWarning() << "Null device; returning!";
//     return;
//   }
  qWarning() << "void OHServer::handleData(int connection)" << *data << connection;
  switch(state)
  {
    case Admin:
    {
      qWarning() << "case Authed:";
      if(data->size() == 4)
      {
	if(*data == Command::serverclose)	// close Server
	  close();
	else if(*data == Command::serverlisten)	// listen 
	  ohlisten(m_serverAdminPassword);
// 	else if(*data == Command::playerlist)	// Print Player List
// 	  device->write(m_GameData->playerXmlList());
	else if(*data == Command::saveGame)	// Save the game 
	{
	  /// TODO: implement saving
	}
	else if(*data == Command::startGame)
	{
	  qWarning() << "Start Game";
	  m_GameData->start();
	}
	else if(*data == Command::serverquit)
	{
	  if(connection == -1)
	  {
	    close();
	    qApp->quit();
	  }
	}
	else if(*data == Command::resetConnections)
	{
	  delete m_GameData;
	  m_GameData = new ServerGameData(this);
	  for(QHash<int, ServerSocket*>::iterator it = m_sockets.begin(); it != m_sockets.end(); ++it)
	  {
	    (*it)->close();
	    (*it)->deleteLater();
	  }
	  m_sockets.clear();
	}
	else if(*data == Command::restartGame)
	{
	  /// TODO: restartGame 
	}
// 	else if(*data == Command::
      }
    }
    case User:
    {
      qWarning() << "case Ident:";      
      if(!data->startsWith("<"))
      {
	if(data->contains(Command::playerlist))
	{
	  if(connection == -1) // Local connection 
	    m_admSocket->write(m_GameData->playerXmlList());
	  else
	    sendPlayerlist(connection);
	  data->replace(Command::playerlist, "");
	}
	if(connection != -1)
	{
	  if(data->contains(Command::playerReady))
	  {
	    m_GameData->playerReady(connection);
	    data->replace(Command::playerReady, "");
	  }
	  if(data->contains(Command::ohsocketIdent))
	  {
	  m_sockets.value(connection)->killSocketTimer();
	  data->replace(Command::ohsocketIdent, "");
	  }
	  
	if(data->contains(Command::claimAdmin))
	{
	  qWarning () << "data->contains(Command::claimAdmin)";
	  data->replace(Command::claimAdmin, "");
	  if(m_serverAdminPassword.isEmpty())
	  {
	    if(connection == -1)
	    {
	      m_admState = Admin;
// 	      delete m_admTimer;
// 	      m_admTimer = 0;
	    }
	    // 	    m_admSocket->write(m_GameData->playerXmlList());
	    else
	      m_sockets.value(connection)->setAdmin(true);
	  }
	  else if(data->startsWith(m_serverAdminPassword))
	    m_sockets.value(connection)->setAdmin(true);
	  
	  data->replace(m_serverAdminPassword, "");
	  if(m_admState == Admin)
	  {
	    qWarning() << "Admin succ. authed!";
	  }
	}
	}
// 	if(data->size() > 0)
	{
// 	  m_GameData->handlePlayerData(*data);
	}
      }
      else
      {
	
// 	m_GameData->handlePlayerData(*data);
      }

      // 	      if(QCryptographicHash::hash(m_serverAdminPassword, QCryptographicHash::Md5) % m_authNr == data)
//       {
// 	delete m_admTimer;
// 	m_admTimer = 0;
// 	m_admState = Authed;
//       }
/*
      else if(m_serverAdminPassword.size() == 0)
      {
	m_admState = Authed;
    }*/
    // 	      else
    ///  {
      // 		m_admTimer->start(2000);
      // 		m_admState = Sleep_Delete;
      ///  }
      /* break;*/
    }
    case New:
    {
      qWarning() << "case New:";
      if(*data == Localserver::Ident)
      {
	m_admState = User;
	if(m_serverAdminPassword.isEmpty())
	{
	  qWarning() << "if(m_serverAdminPassword.isEmpty())";
	  m_admState = Admin;
	  m_admTimer->deleteLater();
	}
	/*else
	{
	  qWarning() << "Adm PW isn't empty, authing???";
	  // 		  m_authNr = (qrand() >> 3) ^ time(NULL) % (qrand() >> 4);
	  // 		  write( QByteArray::number(m_authNr) );
	}*/
      }
      break; 
    } ///........
    default:
      break;
  }
}

void OHServer::kickPlayer(int playerid)
{
  qWarning() << "void OHServer::kickPlayer(int playerid)";
  QTcpSocket *socket =  m_sockets.value(playerid);
  if(socket != 0)
  {
    socket->abort();
  }
}

void OHServer::banPlayer(const QHostAddress &ip)
{
  m_bannedAddresses << ip;
}

// QByteArray OHServer::printPlayerList()
// {
//   QByteArray data;
//   QXmlStreamWriter writer(&data);
//   const QList<Player *> pl = m_GameData->playerList();
//   const QList<Player *>::const_iterator endit = pl.end();
//   QList<Player *>::const_iterator it;
//   
//   writer.writeStartElement("playerlist");
//   writer.writeAttribute("cur", QString::number(m_currentPlayers));
//   writer.writeAttribute("max", QString::number(m_maxPlayers));
//   for(it = pl.begin(); it != endit; ++it)
//   {
//     writer.writeEmptyElement("player");
//     writer.writeAttributes((*it)->xmlAttributes());
//   }
//   writer.writeEndDocument();
//   return data;
// 
// }





/*void OHServer::newPlayer()
{
  QTcpSocket *playerSocket = nextPendingConnection();
    qWarning() << "Incoming:" << playerSocket->peerAddress();
      Player *connectingPlayer = new Player(playerSocket);    
      m_GameData->addPlayer(connectingPlayer);
      m_currentPlayers ++;
          connect(playerSocket, SIGNAL(disconnected()), this, SLOT(playerDisconnected()));

}*/


void OHServer::incomingConnection(int socketDescriptor)
{
  if(m_currentPlayers < m_maxPlayers)
  {
    ServerSocket *socket = new ServerSocket();
    
    if(socket->setSocketDescriptor(socketDescriptor))
    {
      if(m_bannedAddresses.contains(socket->peerAddress() ))
      {
	socket->abort();
	delete socket;
      }
      qWarning() << "Incoming:" << socket->peerAddress() << m_currentPlayers << m_maxPlayers;
      Player *connectingPlayer = new Player(this);
      
      m_sockets[connectingPlayer->id()] = socket;
      socket->setID(connectingPlayer->id());
      socket->write(("IX" + toHex(connectingPlayer->id())).toUtf8());
//       socket->startTimer(5000);
//       qWarning() << ("IX" + toHex(connectingPlayer->id())).toUtf8() << connectingPlayer->id();
      
      m_GameData->addPlayer(connectingPlayer);
      m_currentPlayers ++;
      
      connect(m_pingTimer, SIGNAL(timeout()), socket, SLOT(sendPingRequest()));
      connect(socket, SIGNAL(disconnected(int)), this, SLOT(playerDisconnected(int)));
      connect(socket, SIGNAL(dataAvailable(int)), this, SLOT(handleData(int)));
//       connect(socket, SIGNAL(playerlistRequested(int)), this, SLOT(sendPlayerlist(int)));
//       connect(socket, SIGNAL(playerReady(int)), m_GameData, SLOT(playerReady(int)));
    }
    else
      delete socket;
  }
  else
    close();
}

void OHServer::sendData()
{
  QPair<int, QByteArray> pair(m_GameData->dequeueData());
  sendData(pair.first, pair.second);
}

// send data to socket with the specified id
void OHServer::sendData(int socketID, const QByteArray &data)
{
  qWarning() << "void OHServer::sendData(int socketID, const QByteArray &data)";
  OHSocket *socket = m_sockets.value(socketID);
  if(socket->state() == QAbstractSocket::ConnectedState)
  {
    socket->write(data);
  }
}

void OHServer::broadcastData(const QByteArray &data)
{
//   mutex->lock();
  qWarning() << "Broadcasting Data: " << data.size() << data;
  
//   QList<ServerSocket *> sl = m_sockets.values();

  const QHash<int, ServerSocket *>::iterator endit = m_sockets.end();
  for(QHash<int, ServerSocket *>::iterator it = m_sockets.begin(); it != endit; ++it)
  {
    if(*it != 0)
    {
      if((*it)->state() == QAbstractSocket::ConnectedState)
      {
// 	qWarning() << "To: " << (*it)->peerAddress();
	(*it)->write(data);
      }
    }
  }
//   mutex->unlock();
}

void OHServer::broadcastGameData()
{
  broadcastData(m_GameData->broadcastData());
}

void OHServer::sendPlayerlist(int socketID)
{
  qWarning() << "void OHServer::sendPlayerlist(int socketID) " << socketID;
  //sync socket-ping --> player-ping
  const QHash<int, ServerSocket *>::iterator endit = m_sockets.end();
  for(QHash<int, ServerSocket *>::iterator it = m_sockets.begin(); it != endit; ++it)
  {
    qWarning() << (*it)->id() << (*it)->ping();
    m_GameData->player((*it)->id())->setPing((*it)->ping());
  }
//   qWarning() << m_GameData->playerXmlList();
  sendData(socketID, m_GameData->playerXmlList());
  
}

void OHServer::playerDisconnected(int pid)
{
  m_GameData->finishPlayer(pid);
  ServerSocket *oldsocket = m_sockets.take(pid);
  oldsocket->deleteLater();
  qWarning() << "Player disconnected!";
  m_currentPlayers --;
  if(m_currentPlayers < m_maxPlayers)
  {
//     ohlisten();
  }
  qWarning() << "End of: void OHServer::playerDisconnected(int pid)!";
}
