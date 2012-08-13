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

#include "data/abstractmapobject.h"

int AbstractMapObject::M_IDCounter = 1;



AbstractMapObject::AbstractMapObject(int		a_role,
		     const QString	&a_filename,
		     const QPoint	&a_position,
		     const QString	&a_name,
		     const QString	&a_tooltip,
			   double	a_zvalue,
		     AbstractMap *parent) :
		     m_role (a_role),
		     m_filename	(a_filename),
		     m_position	(a_position),
		     m_name	(a_name),
		     m_tooltip (a_tooltip),
		     m_zValue (a_zvalue),
		     m_parent (parent)
{
  m_id = M_IDCounter;
  M_IDCounter++;

// 	m_role = param_role;
// 	m_filename = param_filename;
// 	m_tooltip = param_tooltip;
// 	m_position = param_position;
// 	m_zValue = param_zvalue;

}

AbstractMapObject::AbstractMapObject(AbstractMap *parent) : m_role (0), m_zValue(0), m_parent (parent)
{
  M_IDCounter++;
  m_id = M_IDCounter;
}


bool operator==(const AbstractMapObject &m1, const AbstractMapObject &m2)
{
//   m1.setRole(m2.role());
//   m1.setFilename(m2.filename());
//   m1.setTooltip(m2.tooltip());
//   m1.setName(m2.name());
//   m1.setPositon(m2.position());
//   m1.setZValue(m2.zValue());
  return ((m1.role() == m2.role()) && (m1.imagepath() == m2.imagepath()) && (m1.tooltip() == m2.tooltip()) && (m1.name() == m2.name()) && (m1.position() == m2.position()) && (m1.zValue() == m2.zValue()));
}

/*operator=(AbstractMapObject &m1, const AbstractMapObject &m2);
{
  m1.setRole(m2.role());
  m1.setFilename(m2.filename());
  m1.setTooltip(m2.tooltip());
  m1.setName(m2.name());
  m1.setPositon(m2.position());
  m1.setZValue(m2.zValue());
  return m1;
}*/
/*void AbstractMapObject::operator=(const AbstractMapObject &m2);
{
  setRole(m2.role());
  setFilename(m2.filename());
  setTooltip(m2.tooltip());
  setName(m2.name());
  setPositon(m2.position());
  setZValue(m2.zValue());
}*/

void AbstractMapObject::setRole (int a_role)
{
  m_role = a_role;
}

void AbstractMapObject::setFilename	(const QString &a_filename)
{
  m_filename = a_filename;
}

void AbstractMapObject::setImagepath	(const QString &a_path)
{
  m_filename = a_path;
}

void AbstractMapObject::setTooltip	(const QString &a_tooltip)
{
  m_tooltip = a_tooltip;
}

void AbstractMapObject::setName	( const QString &a_name)
{
  m_name = a_name;
}

void AbstractMapObject::setPosition(const QPointF &a_pos)
{
  m_position = a_pos;
}

void AbstractMapObject::moveBy (qreal a_xShift, qreal a_yShift)
{
  m_position.rx() += a_xShift;
  m_position.ry() += a_yShift;
}

void AbstractMapObject::setZValue (double a_zvalue)
{
  m_zValue = a_zvalue;
}

void AbstractMapObject::setGraphicType (GraphicType gt)
{
  if(!m_filename.endsWith("svg"))
  {
    if(gt != SVG)
    {
      m_graphicType = gt;
    }
  }
  else
  {
    m_graphicType = SVG;
  }
}


// QString AbstractMapObject::positionS() const
// {
//   return (QString::number(m_position.x()) + "|" + QString::number(m_position.y()));
// }


/*AbstractMapObject::AbstractMapObject(const int		a_role,
		     const QString	&a_filename,
		     const QString	&a_position,
		     const QString	&a_name,
		     const QString &a_tooltip,
		     const qreal a_zvalue) :
		     m_role (a_role),
		     m_filename (a_filename),
		     m_position(toPoint(a_position)),
		     m_name (a_name),
		     m_tooltip (a_tooltip),
		     m_zValue (a_zvalue)
{
  AbstractMapObject_IDCounter++;
  m_id = AbstractMapObject_IDCounter;
//   int c_index = a_position.indexOf("|");
//   m_position.setX(a_position.left(c_index).toInt());
//   m_position.setY(a_position.right(a_position.size() - 1 - c_index).toInt());
//   qWarning() << "AbstractMapObject-Constructor " << m_position << m_filename << " " << (a_position.size() - 1 - c_index) << a_position.right(a_position.size() - 1 - c_index);
  //   for(int i = 0; i < a_position.size(); i++)
//   {
//     if()
//   }

}*/