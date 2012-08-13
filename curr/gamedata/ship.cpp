/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
 *   oh.devs@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; eitherm_version 2 of the License, or    *
 *   (at your option) any laterm_version.                                  *
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

#include "ship.h"
#include "xmlnames.h"
#include "shiptype.h"

#include <math.h>
#include <QtCore/QXmlStreamAttributes>


#include <QtCore/QLineF>

#include <QtDebug>

#include <OQString>

// #define _debug_
/*#ifdef _debug_
#include <QtDebug>
#endif

#ifdef _DEBUG_DESTRUCTORS
#include <QtDebug>
#endif*/

// int Ship::gamespeed = 1;
int Ship::m_idcounter = 0;

Ship::Ship()
{
  
}

Ship::Ship(const Ship &other) : m_id (other.m_id), m_type (other.m_type), m_ownerid (other.m_ownerid), m_name (other.m_name), m_condition (other.m_condition), m_controlCondition (other.m_controlCondition), m_seamen (other.m_seamen), m_cargo (other.m_cargo), m_mass (other.m_mass), m_position (other.m_position), m_v (other.m_v), m_dir (other.m_dir), m_toDir(other.m_toDir), m_settedSailSurface (other.m_settedSailSurface), m_toSettedSailSurface (other.m_toSettedSailSurface), m_maxSailSurface (other.m_maxSailSurface), m_anchored (other.m_anchored)
{
}

Ship::Ship(const ShipType &type, const QString &name) : /*QObject(),*/ m_id (m_idcounter), m_type(type.typeID()), m_name (name), m_condition(type.maxCondition()), m_controlCondition(100), m_seamen(0), m_mass (type.emptyMass()),  m_v (0), m_dir(0), m_toDir(0), m_settedSailSurface (0), m_toSettedSailSurface (0),  m_maxSailSurface(type.maxSailSurface()), m_anchored(true)
{
  m_idcounter ++;
  if(m_name.isEmpty())
    m_name = type.typeName();
  
}


/*Ship::Ship(const QString &param_name) : m_navCalcDelay(1), m_id (m_idcounter), m_name (param_name), m_controlCondition(100)
{
  m_idcounter ++;
  m_cargo.setCapacity( qrand() % 2001);
  
  connect(&m_refreshTimer, SIGNAL(timeout()), this, SLOT(calcPos()));
  setRefreshRate(40); // each 40 msecs the pos of the ship is calced again
}*/

Ship::~Ship()
{
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "Destructing Ship" <<m_name;
#endif
}

void Ship::setOwnerID(int ownerID)
{
  m_ownerid = ownerID;
}

QString Ship::printPosition() const
{
  /*OHDebug(QString("Generic Position: \tX: %1 \tY: %2").arg(m_currentPosition.generic_position.x()).arg(m_currentPosition.generic_position.y())); */
  QString result = QString("M Position: \tX: %1 \tY: %2").arg(m_position.point().x()).arg(m_position.point().y()); 
  result += (QString("Coords: \tX: %1 \tY: %2").arg(m_position.coordinates().x()).arg(m_position.coordinates().y())); 
  
  return result;
}

void Ship::setName(const QString &param_name)
{
  m_name = param_name;
}


void Ship::calcMovement(int windv, const float &winddir)
{
  /*
  if(m_settedSailSurface > m_toSettedSailSurface)
  {
    m_settedSailSurface -= 1;
    if(m_settedSailSurface < 0.05)
    {
      m_settedSailSurface = 0;
    }
  }
  
  else if(m_settedSailSurface < m_toSettedSailSurface)
  {
    m_settedSailSurface += 1;
  }
  #ifdef _debug_
  qWarning() << m_settedSailSurface << m_toSettedSailSurface << " sS << tSS";
  #endif
  // 	if(m_settedSailSurface > 0 && windv > 0)
  {
    if(m_ControlDifficulty == 0)
    {
      float accelerationv = windv * (0.9 + cos(m_dir - winddir))/2 ;
      // 			if(accelerationv >m_v)
      {
	// 				v += (ceil((accelerationv -m_v)/4));
	m_v += (m_settedSailSurface + 0.1) * (accelerationv - m_v)/25;
      }
      if(m_v> 0)
      {
	m_v -= (m_v + 5)/100;
      }
      *////............
      /*			else if(accelerationv <m_v)
      {
	// 				v += (floor((accelerationv -m_v)/4));
	v += (accelerationv -m_v)/20;
      }*//*
      #ifdef _debug_
      qWarning() << accelerationv <<m_v<<m_v/20 << (m_settedSailSurface + 0.1) * (accelerationv -m_v)/25;
      #endif
    }
    #ifndef _SIMPLE_SHIP_CONTROL
    else if(m_ControlDifficulty == 1)
    {
      float acceleration = m_settedSailSurface * windv * cos(m_dir + m_sailDir - winddir) -m_v;
      if(acceleration > 0)
      {
	m_v += int (ceil(acceleration/2));
      }
      else if(acceleration < 0 )
      {
	m_v += int (floor(acceleration/2));
      }
      #ifdef _debug_
      qWarning() << acceleration;
      #endif
    }
    #endif
    #ifdef _debug_
    qWarning() << m_v << "m_v";
    #endif
  }
  
  #ifdef keyboard_control
  if(m_MouseControl)
  {
    if(m_dir != m_toDir)
    {
      if(m_toDir > m_dir - 0.01 && m_toDir < m_dir + 0.01)
      {
	m_dir = m_toDir;
	return;
      }
      
      if((m_dir < m_toDir && m_dir + M_PI > m_toDir) || (m_dir > m_toDir && m_dir - M_PI > m_toDir))
      {
	m_dir = m_dir + 0.001 * ((m_v/2) + 3) * m_controlVelocity;
      }
      else
      {
	m_dir = m_dir - 0.001 * ((m_v/2) + 3) * m_controlVelocity;
      }
      
      if(m_dir < 0)
      {
	m_dir = 2*M_PI-0.0000001;
      }
      else if(m_dir > 2*M_PI)
      {
	m_dir = 0;
      }
    }
  }
  else		//keyboard-control
  {
    if(m_rudderDir != 0 || m_toRudderDir != 0)
    {
      // 			static int delayvar;		// control-delaying-variable
      m_delayvar ++;
//       if(m_delayvar % 10 == 0)
      {
// 	m_delayvar = 1;
	if(m_rudderDir != m_toRudderDir)
	{
	  
	  if(m_toRudderDir < 0 && m_rudderDir > m_toRudderDir)
	  {
	    m_rudderDir += (m_toRudderDir + m_rudderDir)/5;
	  }
	  else if(m_toRudderDir >= 0 && m_rudderDir < m_toRudderDir)
	  {
	    m_rudderDir += (m_toRudderDir - m_rudderDir)/5;
	  }
	  if(m_rudderDir < 0.0001 && m_rudderDir > -0.0001 && m_toRudderDir == 0)
	  {
	    m_rudderDir = 0;
	  }
	  else if(m_rudderDir > 0.1 || m_rudderDir < -0.1)
	  {
	    m_rudderDir = 0;
	  }
	}
      }
      m_dir += m_rudderDir;
      
      if(m_dir < 0)
      {
	m_dir = 2*M_PI-0.0000001;
      }
      else if(m_dir > 2*M_PI)
      {
	m_dir = 0;
      }
    }
  }
  #endif
  if(m_anchored)
  {
    m_v = 0;
//     if(m_v < 3)
//     {
//       m_v = m_v / 2;
//       // 			m_toDir = m_dir + 1;
//     }
//     else
//     {
//       m_v = 4 * m_v/5;
//       // 			m_toDir = m_dir + 1;
//       
//     }
    
  }
  */
}


void Ship::anchor()
{
m_anchored = true;
m_toSettedSailSurface = 0;
}

void Ship::brake(const float &param_brakefactor)
{
  m_v *= 1 - param_brakefactor;

}



void Ship::set_ToSettedSailSurface(float param_amount)
{
  if(param_amount >= 0 && param_amount <= m_maxSailSurface)
  {
    if(param_amount < 0.01)
    {
      m_toSettedSailSurface = 0;
      // 		return;
    }
    else
      m_toSettedSailSurface = param_amount;
    
    #ifdef _debug_
    qWarning() << "void Ship::set_ToSettedSails(float param_amount)" << param_amount;
    #endif
  }
}

#ifndef _SIMPLE_SHIP_CONTROL
void Ship::set_SailDir(float param_dir)
{
  if(param_dir <= 0.3 && param_dir >= -0.3)
  {
    m_sailDir = param_dir;
  }
}

void Ship::set_ToRudderDir(float param_dir)
{
  if(param_dir <= const_max_rudder_deflection && param_dir >= - const_max_rudder_deflection)
  {
    m_toRudderDir = param_dir;
  }
}
#endif

// void Ship::set_ToDir(float param_dir)
// {
//   if(param_dir <= 2 * M_PI && param_dir >= 0)
//   {
//     m_toDir = param_dir;
//   }
// }


void Ship::setDirToPoint(const QPointF &point)
{
  QLineF line(point, m_position.point());
  m_toDir = line.angle();
  
//   int dx = point.x() - m_pos.point().x(), dy = point.y() - m_pos.point().y();
  
}

void Ship::calcPos()
{
  
  if(m_dir != m_toDir)
  {
    if(m_toDir - m_dir > 0.01)
      // 			else if((m_dir < m_toDir && m_dir + M_PI > m_toDir) || (m_dir > m_toDir && m_dir - M_PI > m_toDir))
      {
// 	m_dir = m_dir + 0.0005 * ((m_v/2) + 2) * m_controlCondition * gamespeed * m_navCalcDelay;
      }
      else if(m_toDir - m_dir < 0.01)
      {
// 	m_dir = m_dir - 0.0005 * ((m_v/2) + 2) * m_controlCondition * gamespeed * m_navCalcDelay;
      }
      else
      {
	m_dir = m_toDir;
      }
      
      if(m_dir < - M_PI)
      {
	m_dir = M_PI;
      }
      else if(m_dir > M_PI)
      {
	m_dir = - M_PI;
      }
  }

// 	m_currentPosition.generic_position.setX(m_currentPosition.generic_position.x() - (m_v * sin(m_dir))/10);
// 	m_currentPosition.generic_position.setY(m_currentPosition.generic_position.y()  - (m_v * cos(m_dir))/10);
// 	m_position.setPoint(QPoint(m_position.point().x()  - (m_v * sin(m_dir))/10, m_position.point().y()  - (m_v * cos(m_dir))/10));
}

// void Ship::setGameSpeed(int newSpeed)
// {
//   gamespeed = newSpeed;
// }


/*void Ship::setRefreshRate(int msecs)
{
  m_navCalcDelay = msecs/40;
  m_refreshTimer.start(msecs);
}*/

void Ship::setPosition(const Position &param_destinationposition)
{
  m_position = param_destinationposition;
}


bool Ship::setCargo(const Goods &param_newcargo)
{
m_cargo = param_newcargo;
return true;
}

void Ship::setSeamen(int number)
{
  m_seamen = number;
}

QXmlStreamAttributes Ship::state() const
{
  QXmlStreamAttributes list;
  list << QXmlStreamAttribute(XmlName::name, m_name);
  list << QXmlStreamAttribute(XmlName::mass, QString::number(m_mass));
  list << QXmlStreamAttribute(XmlName::seamen, QString::number(m_seamen));
  list << QXmlStreamAttribute(XmlName::condition, QString::number(m_condition));
  list << QXmlStreamAttribute(XmlName::controlcondition, QString::number(m_controlCondition));
  return list;
}

QXmlStreamAttributes Ship::characteristics() const
{
  QXmlStreamAttributes list;

	  list << QXmlStreamAttribute("v", QString::number(m_v));
	  list << QXmlStreamAttribute("dir", QString::number(m_dir));
	  list << QXmlStreamAttribute("toDir", QString::number(m_toDir));
	  list << QXmlStreamAttribute("sails", QString::number(m_settedSailSurface));
	  list << QXmlStreamAttribute("tosails", QString::number(m_toSettedSailSurface));
	  
	  #ifndef _SIMPLE_SHIP_CONTROL
	  list << QXmlStreamAttribute("sailDir", QString::number(m_sailDir));
	  list << QXmlStreamAttribute("rudderDir", QString::number(m_rudderDir));
	  #endif

	  list << QXmlStreamAttribute("px", QString::number(m_position.point().x()));
	  list << QXmlStreamAttribute("py", QString::number(m_position.point().y()));
// 	  list << QXmlStreamAttribute("cx", QString::number(m_position.coordinates().x()));
// 	  list << QXmlStreamAttribute("cy", QString::number(m_position.coordinates().y()));
	  list << QXmlStreamAttribute(XmlName::coordinates, StringFromPoint(m_position.coordinates()));
	  list << QXmlStreamAttribute("anchored", QString::number(((int)(m_anchored))));
   
  return list;
}

void Ship::setState(const QXmlStreamAttributes &attributes)
{
  bool ok; bool result = true;
  m_name = attributes.value(XmlName::name).toString();
  m_mass = attributes.value(XmlName::mass).toString().toInt(&ok);				result &= ok;
  m_seamen = attributes.value(XmlName::seamen).toString().toInt(&ok);				result &= ok;
  m_condition = attributes.value(XmlName::condition).toString().toFloat(&ok);			result &= ok;
  m_controlCondition = attributes.value(XmlName::controlcondition).toString().toInt(&ok);	result &= ok;
  if(!result)
  {
    qWarning() << ("Error while setting Ship::State!!");
  }
}

void Ship::setNavCharacteristics(const QXmlStreamAttributes &attributes)
{
  bool ok; bool result = true;
  m_v			= attributes.value("v").toString().toFloat(&ok);	result &= ok;
  m_dir			= attributes.value("dir").toString().toFloat(&ok);	result &= ok;
  m_toDir		= attributes.value("dir").toString().toFloat(&ok);	result &= ok;
  m_settedSailSurface		= attributes.value("sails").toString().toFloat(&ok);	result &= ok;
  m_toSettedSailSurface 	= attributes.value("tosails").toString().toFloat(&ok);	result &= ok;
  
  #ifndef _SIMPLE_SHIP_CONTROL
  m_sailDir		= attributes.value("saildir").toString().toFloat(&ok);	result &= ok;
  m_rudderDir		= attributes.value("rudderDir").toString().toFloat(&ok);result &= ok;
  #endif
  
  m_position.setPoint(StringToPoint(attributes.value(XmlName::point).toString()));
//   m_position.setPoint(QPoint(attributes.value("px").toString().toInt(&ok), attributes.value("py").toString().toInt(&ok)));		result &= ok;
//   m_position.point().setY(attributes.value("py").toString().toFloat(&ok));	result &= ok;
  m_position.setCoordinates(StringToPoint(attributes.value(XmlName::coordinates).toString()));
  if(!result)
  {
    qWarning() << "Error while setting Ship::NavCharacteristics!!";
  }
}

void Ship::operator=(const Ship &other)
{
  m_id = other.m_id;
  m_mass = other.m_mass;
  m_position = other.m_position;
  m_ownerid = other.m_ownerid;
  m_cargo = other.m_cargo;
  m_type = other.m_type;
  m_v = other.m_v;
  m_dir = other.m_dir;
  m_settedSailSurface = other.m_settedSailSurface;
  m_condition = other.m_condition;
  m_controlCondition = other.m_controlCondition;
  m_seamen = other.m_seamen;
//   return this;
}

Ship loadShip(const QXmlStreamAttributes &attributes)
{
  int typeID = attributes.value(XmlName::type).toString().toInt();
  QString typeFile = attributes.value(XmlName::typeFile).toString();
//   if(QFile::exists(typeFile))
//   {
    return Ship(ShipType(typeFile));
//   }
}