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

#include "maphandler.h"
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>
#include <QtGui/QImage>

#include <QtGui/QWidget>
#include <QtGui/QLabel>

#include <QtCore/QBuffer>
#include <QtCore/QFile>

#include <OQString>

#include <networkcommands.h>

void rgbsquare(const QImage *, QRgb *, int x, int y);

void maphandling(const QImage *image, int cityCount)
{
  qWarning() << "Maphandling";
  QLocalServer server;
  QLocalServer::removeServer(Localserver::Mapserver);
  qWarning() << "server.listen(Localserver::Mapserver)!";
  if(server.listen(Localserver::Mapserver))
  {
    if(server.waitForNewConnection(120000)) //waits 2 mins for connection
    {
      QLocalSocket *socket = server.nextPendingConnection();
      qWarning() << "QLocalSocket *socket = server.nextPendingConnection();" << Localserver::Mapserver;
      QImage *newImage = new QImage(*image);
      //       int cityCount = socket.readAll().toInt();
      qWarning() << "City Count: " << cityCount;
      const int xmax (newImage->width()), ymax (newImage->height());
      QRgb rgbarr[9];
      int x = qrand() % xmax; int y = qrand() % ymax;
      int landf(0); int waterf(0); int cityf(0);
      bool ok (false);
      QList <QPoint> pointlist;
      for(int i = cityCount; i; i--)
      {
	qWarning() << "for(int i = cityCount; i; i--)";
	while(!ok)
	{
	  rgbsquare(newImage, rgbarr, x, y);
	  for(int pi = 8; pi; pi--)
	  {
	    if(qBlue(rgbarr[pi]) < qGreen(rgbarr[pi])/2)
	    {
	      landf ++;
	    }
	    else if(qBlue(rgbarr[pi]) > qGreen(rgbarr[pi]))
	    {
	      waterf ++;
	    }
	    else if(qRed(rgbarr[pi] == 0xFF))
	    {
	      cityf ++;
	    }
	    else
	    {
	      qWarning() << "Unknown Colour!" << rgbarr[i];
	    }
	  }
	  
	  if(landf > 3 && waterf > 2 && cityf == 0)
	  {
	    pointlist << QPoint(x,y);
	    newImage->setPixel(x,y, 0xFF0000);
	    newImage->setPixel(x+1,y, 0xFF0000);
	    newImage->setPixel(x,y-1, 0xFF0000);
	    newImage->setPixel(x-1,y, 0xFF0000);
	    newImage->setPixel(x,y+1, 0xFF0000);
	    qWarning() << "City at:" << x << y;
	    ok= true;
	  }
	  x = (qrand() % (xmax - 2)) + 1;
	  y = (qrand() % (ymax - 2)) + 1;
	  landf = 0;
	  cityf = 0;
	  waterf = 0;
	}
	ok = false;
      }
      
      QString filename = QString::number(time(NULL)) + ".png";
      newImage->save(filename, "PNG");
      
      QByteArray sendData (QByteArray::number(pointlist.size()) + "\n");
      const QList<QPoint>::const_iterator endit = pointlist.end();
      for(QList<QPoint>::const_iterator it = pointlist.begin(); it != endit; ++it)
      {
	sendData.append(StringFromPoint(*it) + "\n");
      }
      sendData.append(filename);
      socket->write(sendData);
      socket->waitForBytesWritten(10000);
    }
    else
      qWarning() << server.errorString();
  }
  else
    qWarning() << server.errorString();
}

void rgbsquare(const QImage *image, QRgb *rgbarr, int x, int y)
{
  for(int i = 0; i < 9; i++)  
  {
    rgbarr[i] = image->pixel(x,y);
    switch(i)
    {
      case 0:
      case 6:
      case 7:
      {
	y--;
	break;
      }
      case 4:
      case 5:
      {
	x--;
	break;
      }
      case 2:
      case 3:
      {
	y++;
	break;
      }
      case 1:
      {
	x++;
	break;
      }
    }
  }
}