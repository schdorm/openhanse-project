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

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QResource>

#include <QtDebug>

#include "server.h"

int main(int argc, char *argv[])
{

//   for(int i = 0; i!= argc+1; i++)
//     qWarning() << argv[i] << argc << qHash(argv[i]) << time(NULL) << 
  
  qsrand((time(NULL) ^ qHash(argv[0])) >> argc );
//   QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath () + QDir::separator() + "lib");
  QResource::registerResource("data/images.rcc");
  QResource::registerResource("data/data.rcc");

  QCoreApplication app(argc, argv);
//   foreach (QString path, app.libraryPaths())	
//     qWarning() << path;
  QStringList serverpw = app.arguments().filter("--pw=");
  
  OHServer server;
  qWarning() << "Serverpw: \t" << serverpw.size();
  
  serverpw.append("ohstdpw");
  
  qWarning() << "Serverpw: \t" << serverpw.first();
  server.ohlisten(serverpw.first().remove("--pw="));
  
  return app.exec();
}
