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

#ifndef NETWORK_COMMANDS_H
#define NETWORK_COMMANDS_H

/*
#define Command_playerlist "RQPL"
#define Command_savegame "SAVE"
#define Command_startgame "STRT"
#define Command_serverlisten "LISN"
#define Command_serverclose "CLOS"
#define Command_serverquit "QUIT"
#define Command_pingrequest "PING"
#define Command_pinganswer "PONG"

#define Localserver_Name "oh_localserver"
#define Localserver_Ident "OH local server control connection"
/*/
namespace Command
{
  extern const char *playerlist;	// = "RQPL";
  extern const char *saveGame;		// = "SAVE";
  extern const char *playerReady;
  extern const char *startGame;		// = "STRT";
  extern const char *restartGame;
  extern const char *resetConnections;
  extern const char *serverlisten;	// = "LISN";
  extern const char *serverclose;	// = "CLOS";
  extern const char *serverquit;	// = "QUIT";
  extern const char *pingrequest;	// = "PING";
  extern const char *pinganswer;	// = "PONG"; // pingresponse
  extern const char *ohsocketIdent;	// = "OHSI"
  extern const char *kickPlayer;	// = "KICK"
  extern const char *banPlayer;		// = "BANN"
  extern const char *claimAdmin;	// = "CADM"
  

}

namespace Network
{
  extern const char *EndOfFile;
  extern const char *ohstdpw;
}

namespace Localserver
{
  extern const char *Name;// = "oh_localserver";
  extern const char *Ident;// = "OH local server control connection";
  extern const char *Mapserver;
  extern const char *MapserverRuns;
}
// */
#endif

