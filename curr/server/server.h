/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
 *   schdorm@googlemail.com                                                *
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

#ifndef _Server_H
#define _Server_H

#include <QtCore/QObject>
#include <QtNetwork/QTcpServer>

#include "serversocket.h"

class QUdpSocket;
class QLocalServer;
class QLocalSocket;
class QTimer;

class ServerGameData;


// class QMutex;
// #include <Player>

const int defaultMaxPlayers = 10;

class OHServer : public QTcpServer
{
  Q_OBJECT
  public:
    OHServer(QObject *parent = 0);
    void ohlisten(const QString &);
    
    void broadcastData(const QByteArray &);
    void sendData(int, const QByteArray &);
    
    enum AdmStates
    {
      null = 0,
      New = 0x2, // new connection without identification
      User = 0x4,
      Admin = 0xa,
      Sleep_Delete = 0xd		// waits some seconds before deleting socket with false auth ...
      
    };
    int currentPlayers() const { return m_currentPlayers; }
    int maxPlayers() const { return m_maxPlayers; }
    
    
    
  public slots:
    void enableAdmServer();
    void handleAdmConnection();
    void handleData(int);
    
    void sendPlayerlist(int);
    void broadcastGameData();
    
    void sendData();
//     void newPlayer();
    
  signals:
    
  private:
    QLocalServer *m_admServer;
    QLocalSocket *m_admSocket;
    QUdpSocket *m_nameBroadcaster;
    
    ServerGameData *m_GameData;
    
    QTimer *m_admTimer;
    AdmStates m_admState;
    QByteArray m_serverAdminPassword;
    int m_authNr;
    
    QHash <int, ServerSocket*> m_sockets;
    
    QList<QHostAddress> m_bannedAddresses;
    
    QTimer *m_pingTimer;
//     QMutex *mutex;
    
  private slots:
    void playerDisconnected(int);
    
  protected:
    void kickPlayer(int);
    void banPlayer(const QHostAddress &);
    
    void incomingConnection(int);
    int m_maxPlayers;
    int m_currentPlayers;

};

#endif
