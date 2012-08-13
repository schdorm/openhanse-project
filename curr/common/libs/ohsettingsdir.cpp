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

#include "ohsettingsdir.h"
#include <QtDebug>
#include <QtCore/QDir>

QString settingsdir()
{
  QString path;
  #ifdef linux
  QDir dir (QDir::home());
  if(!dir.cd(".OpenHanse"))
  {
    if(!dir.mkdir(".OpenHanse"))
      qWarning() << "Could not create directory!";
    if(!dir.absolutePath().contains(".OpenHanse"))
      if(!dir.cd(".OpenHanse"))
	return QDir::current().absolutePath();						//not a beautiful solution, but enough for now ;-)
  }
  if(!dir.cd("settings"))
  {
    if(!dir.mkdir("settings"))
      qWarning() << "Could not create directory!";
    if(!dir.absolutePath().contains(".OpenHanse/settings"))
      if(!dir.cd("settings"))
	qWarning() << "Could not change to settings-directory!";
  }
  path = dir.absolutePath();

//   SETTINGS->readConfigs(QDir::home().absolutePath().append("/.OpenHanse/cfg.ohc"));
  //reads the configuration file in ~/.OpenHanse/cfg.ohc
  
//   #elif defined win32
  #else
  QDir dir(QDir::current);
  if(!dir.cd("settings"))
  {
    if(!dir.mkdir("settings"))
      qWarning() << "Could not create Settings directory!";
    if(!dir.cd("settings")
      qWarning() << "Could not change to settings-directory!";
  }
  path = dir.absolutePath();
  #endif
  if(!path.endsWith("/"))
    path.append("/");
  return path;
}