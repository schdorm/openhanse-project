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

#include "ohsocket.h"
#include "networkcommands.h"

#include <QtCore/QTimerEvent>

OHSocket::OHSocket (QObject *parent) : QTcpSocket(parent)//, m_pingTimer(new QTimer(this))
{
  //   setPingIntervall(ping_delay);
  connect(this, SIGNAL(readyRead()), this, SLOT(firstDataHandling()));
  //   connect(m_pingTimer, SIGNAL(timeout()), this, SLOT(sendPingRequest()));
  m_timerID = startTimer(5000);
}


/*void OHSocket::setPingIntervall(int msecs)
{
//   m_pingTimer->start(msecs);
}*/


void OHSocket::sendPingRequest()
{
  qWarning() << "void OHSocket::sendPingRequest()";
  if(state() == QAbstractSocket::ConnectedState)
  {
    write("PING");
    m_pingTime = QTime::currentTime();
  }
}


void OHSocket::sendPingAnswer()
{
  qWarning() << "void OHSocket::sendPingAnswer()";
  if(state() == QAbstractSocket::ConnectedState)
  {
    write("PONG");
  }
}

void OHSocket::firstDataHandling()
{
  m_bufferedData = readAll();
  
  qWarning() << "void OHSocket::handleSocketData()" << m_bufferedData << m_bufferedData.size();
  
  if(m_bufferedData.size() <= 8)
  {
    if(m_bufferedData.size() == 4)
    {
      if(m_bufferedData == Command::pingrequest)
      {
	sendPingAnswer();
      }
      else if(m_bufferedData == Command::pinganswer)
      {
	m_ping = m_pingTime.msecsTo(QTime::currentTime());
	qWarning() << "Ping: " << m_ping;
      }
      else emit dataUnhandled();
    }
    else if(m_bufferedData.size() == 8)
    {
      if(m_bufferedData.contains(Command::pinganswer))
      {
	m_ping = m_pingTime.msecsTo(QTime::currentTime());
	qWarning() << "Ping: " << m_ping;
	m_bufferedData.replace(Command::pinganswer, "");
      }
      if( m_bufferedData.contains(Command::pingrequest))
      {
	sendPingAnswer();
	m_bufferedData.replace(Command::pingrequest, "");
      }
      if(m_bufferedData.size() > 0)
      {
	emit dataUnhandled();
      }
    }
    else
      emit dataUnhandled();
  }
  else
  {
    emit dataUnhandled();
  }
}

/*void OHSocket::disconnectFromHostSlot()
{
  disconnectFromHost();
}*/

void OHSocket::timerEvent(QTimerEvent *event)
{
  qWarning() << "void OHSocket::timerEvent(QTimerEvent *) --- Timer event occured" << event->timerId();
  deleteLater();
}

void OHSocket::killSocketTimer()
{
  qWarning() << "void OHSocket::killSocketTimer()" << m_timerID;
  killTimer(m_timerID);
}