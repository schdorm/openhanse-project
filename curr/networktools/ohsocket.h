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

#ifndef _OHSocket_H
#define _OHSocket_H

#include <QtNetwork/QTcpSocket>
#include <QtCore/QTime>

#include <QtCore/QTimer>

// class QTimer;

const int ping_delay = 2000; // time intervall in msecs between ping requests

class OHSocket : public QTcpSocket
{
  Q_OBJECT
  public:
    OHSocket(QObject * = 0);
//     void setPingIntervall(int);
    void sendPingAnswer();
    
    int ping() const { return m_ping; }
    
    const QByteArray & bufferedData() const { return m_bufferedData; }
    void killSocketTimer();
    
  signals:
    void dataUnhandled();
    
  public slots:
    void sendPingRequest();
    void firstDataHandling();
//     void disconnectFromHostSlot();
    
    
  protected:
    void timerEvent(QTimerEvent *);
    
    QTime m_pingTime;
//     QTimer *m_pingTimer;
    int m_ping;
    int m_timerID;
    QByteArray m_bufferedData;
};

#endif