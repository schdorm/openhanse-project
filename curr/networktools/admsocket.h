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

#ifndef _OHAdmSocket_H
#define _OHAdmSocket_H

#include <QtNetwork/QLocalSocket>

// class QXmlStreamAttributes;
class QTimer;

class AdmSocket : public QLocalSocket
{
  Q_OBJECT
  public:
    AdmSocket(QObject *parent = 0);
    ~AdmSocket();
    

    
    enum Command{Listen, Close, StartGame, RestartGame, SaveGame, Quit, PlayerlistRequest};
    
    int refreshRate() const 	{ return m_refreshRate; }
    QByteArray players();
    void sendAuth(const QString &auth);
    
    void sendCommand(Command);
    
  public slots:
    void ohconnect();
    void ident();
    void restartGame();
    void saveGame();
    
    
    void setRefreshRate(int);
    void requestPlayerList();
    
    void handleData();
    
  signals:
    void playersRefreshed();
    void mapserverStarted();
    
  private:
    int m_maxPlayers;
    int m_currentPlayers;
    int m_refreshRate;
    
    QTimer *m_refreshTimer;
    
  protected:
    QByteArray m_players;
};

#endif
