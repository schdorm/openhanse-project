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

#include "networkcommands.h"

namespace Command
{
  const char *playerlist = "RQPL";
  const char *saveGame = "SAVE";
  const char *playerReady = "REDY";
  const char *startGame = "STRT";
  const char *restartGame = "REST";
  const char *resetConnections = "RSCN";
  const char *serverlisten = "LISN";
  const char *serverclose = "CLOS";
  const char *serverquit = "QUIT";
  const char *pingrequest = "PING";
  const char *pinganswer = "PONG";
  const char *ohsocketIdent = "OHSI";
  const char *kickPlayer = "KICK";
  const char *banPlayer = "BANN";
  const char *claimAdmin = "CADM";
  
}

namespace Network
{
  const char *EndOfFile = "/EOF";
  const char *ohstdpw = "ohstdpw";
}


namespace Localserver
{
  const char *Name = "oh_localserver";
  const char *Ident = "OHSC"; //"OH local server control connection";
  
  const char *Mapserver = "oh_mapserver";
  const char *MapserverRuns = "MSRN";
}