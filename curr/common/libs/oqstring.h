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

#ifndef _my_string
#define _my_string

#include <QtCore/QString>

//#define USE_SETVALID

class QSize;
class QPoint;


QString removeWithespace(const QString &string);
QString removeWithespaceRef(QString &string);

#ifdef USE_SETVALID

 QString setValid(const QString &a_string);	// if argument is an empty string, "0" will be returned 
 QString getFromValid(const QString &a_string);
 
#endif

QString StringFromPoint(const QPoint &a_point);
QString StringFromPoint1(const QPoint &a_point);
QPoint  StringToPoint(const QString &);

QString StringFromSize(const QSize &a_size);
QSize StringToSize(const QString &);

QString fromBool(bool boolean);
/*{
  if(boolean)
    return "true";
  else
    return "false";
}*/

bool toBool(const QString &string);
/*{
  return (string == "true" || string.toInt() == 1);
}*/

bool toBool(const QStringRef stringref);

#endif
