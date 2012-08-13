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

#include "data/abstractcity.h"
#include "libs/oqstring.h"
#include <QtCore/QXmlStreamAttributes>


#ifdef DEBUG_CITY
#include <QtDebug>
int AbstractCity::M_citycounter = 0;

AbstractCity::~AbstractCity()
{
  static int citydestrkt;
  citydestrkt ++;
  M_citycounter --;
  qWarning() << "AbstractCity destruktor" << citydestrkt << " Diff:" << M_citycounter;
}
/*AbstractCity::AbstractCity(const QXmlStreamAttributes &attributes)
  : m_id (attributes.value("id").toString().toInt()),
  m_name (attributes.value("name").toString())
{
//  m_id = attributes.value("id").toString().toInt();
//  m_name = attributes.value("name").toString();
}*/
#endif

/*AbstractCity::AbstractCity(const AbstractCity &other) : QObject(), m_id(other.id()),  m_name (other.name()), m_production(other.production())
{
  #ifdef DEBUG_CITY
  M_citycounter ++;
  qWarning() << "AbstractCity counter:" <<citycounter;
  #endif
}*/



AbstractCity::AbstractCity(const QString &param_cityname, QObject *parent) : QObject(parent), m_name (param_cityname)
{
  /*
  #ifdef DEBUG_CITY
  static int cc;
  cc++;
  M_citycounter ++;
  qWarning() << "Count of city instances:" << citycounter << "all:" << cc;
  #endif*/
  static int idcounter;
  m_id = idcounter;
  idcounter++;
}

/*AbstractCity::AbstractCity(QObject *parent) : QObject(parent)
{
  
}*/

void AbstractCity::setID(int a_newID)
{
  m_id = a_newID;
}

void AbstractCity::setName(const QString &name)
{
  #ifdef DEBUG_CITY
    qWarning() << "set Name" << name;
    qWarning() << "m_name" << m_name;
  #endif
  
  m_name = name;
  
  #ifdef DEBUG_CITY
    qWarning() << "Name set" << m_name;
  #endif
}


QXmlStreamAttributes AbstractCity::xmlAttributes() const
{
  QXmlStreamAttributes list;
  
  list << QXmlStreamAttribute("id", QString::number(m_id));
  list << QXmlStreamAttribute("name", m_name);
  
  return list;
}

void AbstractCity::setXmlAttributes(const QXmlStreamAttributes &attributes)
{
  m_id = attributes.value("id").toString().toInt();
  m_name = attributes.value("name").toString();
}


void AbstractCity::setProduction(int quality, const QString &param_listing)		// quality = Low Production / Medium / High .....
{
  QString listing = removeWithespace(param_listing);		// removes any whitespace --> "qstring.h"
  QString goodID;
  
  #ifdef DEBUG_CITY
  qWarning() << "void AbstractCity::setProduction(int quality, const QString &param_listing)" << listing << listing.size();
  #endif

  		// iterating through string; when reaching "," --> production of that GOODID = quality
		
  for(int i = 0; i < listing.size(); i ++)
  {
    if(listing[i] == QChar(','))
    {
      #ifdef DEBUG_CITY
      qWarning() << "Set Production: " << goodID.toInt() << quality;
      #endif
      m_production[goodID.toInt()] = quality;
      goodID = QString();
    }
    else
      goodID.append(listing[i]);
  }
}

AbstractCity &AbstractCity::operator=(const AbstractCity &other)
{
  this->m_id = other.id();
  this->m_production = other.production();
  this->m_name = other.name();
  return *this;
}

/*
// void AbstractCity::setID(const QList<int> &idlist)
// {
// 	int i = 0;
// 	while(m_id < 0)
// 	{
// 		i++;
// 		if(!idlist.contains(i))
// 		{
// 		m_id = i;
// 		}
// 	}
// }
// 
// void AbstractCity::setID(int id)
// {
//   m_id = id;
// }*/

