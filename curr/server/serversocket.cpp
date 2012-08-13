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

#include <QtDebug>

#include "serversocket.h"

#include <networkcommands.h> 


ServerSocket::ServerSocket (QObject *parent) : OHSocket(parent), m_adm(false)//, m_ident(false)
{
  connect(this, SIGNAL(dataUnhandled()), this, SLOT(handleData()));
  connect(this, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
}

/*ServerSocket::~ServerSocket()
{
  qWarning() << "ServerSocket::~ServerSocket() ---> deleting ServerSocket";
}*/

void ServerSocket::setID(int newID)
{
  m_id = newID;
}

void ServerSocket::setAdmin(bool isAdm)
{
  m_adm = isAdm;
}

void ServerSocket::handleData()
{
/*  qWarning() << "void ServerSocket::handleSocketData()" << m_bufferedData << m_bufferedData.size();
  int datasize = m_bufferedData.size();
  if((!(datasize % 4)) && datasize < 20)
  {
    if(m_bufferedData.contains(Command::playerlist))
    {
//       qWarning() << "Playerlist requested; ID: " << m_id;
      emit playerlistRequested(m_id);
    }
    else if(m_bufferedData.contains(Command::ohsocketIdent))
    {
//       m_ident = true;
      killSocketTimer();
    }
    else if(m_bufferedData.contains(Command::playerReady))
    {
      emit playerReady(m_id);
    }
    else
      emit dataAvailable(m_id);
  }
  else*/
emit dataAvailable(m_id);
}


// void ServerSocket::handleData() // moved to "server.cpp" to avoid collisions with namespace Command
/*{
  qWarning() << "void ServerSocket::handleSocketData()" << m_bufferedData;
  if(m_bufferedData.size() == 4)
  {
    if(m_bufferedData == Command::playerlist)
    {
      emit playerlistRequested(m_id);
    }
  }
  else
    emit dataAvailable(m_id);
}*/


void ServerSocket::socketDisconnected()
{
  qWarning() << "void ServerSocket::socketDisconnected()";
  emit disconnected(m_id);
}
