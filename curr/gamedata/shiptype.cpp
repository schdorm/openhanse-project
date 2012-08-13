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

#include "shiptype.h"

#include <QtCore/QFile>

#include <QtDebug>

ShipType::ShipType() : m_typeID (-1)
{
  
}

ShipType::ShipType(const QString &descfile) : m_typeID (-1), m_emptyMass (0), m_maxCondition (0), m_minSeamen (0), m_maxSailSurface (0)
{
  qWarning() << "ShipType::ShipType(const QString &descfile) : m_typeID (-1), m_emptyMass (0), m_maxCondition (0), m_minSeamen (0), m_maxSailSurface (0)";
  QFile file(descfile);
  if(file.open(QIODevice::ReadOnly))
  {
    char *src = new char[255];
    char lastchar;
    int c (-1);
    int pos (0);
    enum attributes
    {
      ID,
      Mass,
      Name,
      Crew,
      Condition,
      Capacity,
      Surface,
      File,
      none
    } attr = none;
    
    while(!file.atEnd())
    {
      qWarning() << "Loop 1";
      do
      {
	c++;
	file.getChar(&src[c]);
	qWarning() << "Loop 2, src[c]:" << src[c] << c;
      }
      while(src[c] != ' ' && src[c] != '\n' && !file.atEnd() );
      
      lastchar = src [c];
      src[c] = '\0'; // last character - either space character or new line character is set to terminating character
//       qWarning() << "POS:" << pos << "C:" << c << "SRC:" << src;
      
      if(pos == 0)
      {
	qWarning() << "Switch 1; src[0]" << src[0] << src;
	switch(src[0])
	{
	  case 'i':	//type-id
	  {
	    attr = ID;
	    qWarning() << " attr  = ID";
	    break;
	  }
	  case 'n':	//type-name
	  {
	    attr = Name;
	    break;
	  }
	  case 'm':	//mass
	  {
	    attr = Mass;
	    break;
	  }
	  case 'c':	//crew or condition
	  {
	    if(QString(src) == "crew")
	    {
	      attr = Crew;
	    }
	    else if(QString(src) == "condition")
	    {
	      attr = Condition;
	    }
	    else if(QString(src) == "capacity")
	    {
	      attr = Capacity;
	    }
	    break;
	  }
	  case 's':	//sail-surface
	  {
	    attr = Surface;
	    break;
	  }
	  case 'f':	//file
	  {
	    attr = File;
	    break;
	  }
	  default:
	  {
	    attr = none;
	    break;
	  }
	    
	}
// 	pos = 1;
      }
      else if(pos == 1)
      {
	qWarning() << "Switch 2";
	switch(attr)
	{
	  case ID:
	  {
	    m_typeID = QString(src).toInt();
	    qWarning() << "ID: " << m_typeID << "QString(src): " << QString(src);
	    break;
	  }
	  case Name:
	  {
	    m_typeName = QString(src);
	    qWarning() << "Name: " << m_typeName;
	    break;
	  }
	  case Mass:
	  {
	    m_emptyMass = QString(src).toInt();
	    break;
	  }
	  case File:
	  {
	    m_file = QString(src);
	    break;
	  }
	  case Surface:
	  {
	    m_maxSailSurface = QString(src).toFloat();
	    break;
	  }
	  case Condition:
	  {
	    m_maxCondition = QString(src).toInt();
	    break;
	  }
	  case Crew:
	  {
	    m_minSeamen = QString(src).toInt();
	    break;
	  }
	  case Capacity:
	  {
	    m_capacity = QString(src).toInt();
	    break;
	  }
	  default:
	    break;
	  
	}
      }
      
      if(lastchar == ' ')
	pos ++;
      else
	pos = 0;
      c = -1;
    }
    
    delete src;
    file.close();
  }
  qWarning() << "ID: " << m_typeID;
  qWarning() << "Name: " << m_typeName;
  qWarning() << "Mass: " << m_emptyMass;
  qWarning() << "Condition: " << m_maxCondition;
  qWarning() << "Capacity: " << m_capacity;
  qWarning() << "Crew: " << m_minSeamen;
  
  
}
