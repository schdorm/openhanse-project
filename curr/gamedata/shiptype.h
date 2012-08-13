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
#ifndef _SHIPTYPE_H
#define _SHIPTYPE_H


#include <QtCore/QString>


class ShipType 
{
  public:
    ShipType();
    ShipType(const QString &);
    const QString &typeName	() const	{	return m_typeName;		}
    int typeID			() const	{	return m_typeID;		}
    int maxCondition		() const	{	return m_maxCondition;		}
    int minSeamen		() const 	{	return m_minSeamen;		}
    int emptyMass		() const	{	return m_emptyMass;		}
    
    float maxSailSurface	() const 	{	return m_maxSailSurface;	}
    
    const QString &file 	() const 	{	return m_file;			}
    
  protected:
    int m_typeID;				// type-id
    QString m_typeName;			// typename
    int m_emptyMass;
    int m_maxCondition;			// Zustand allgemein ...
    int m_capacity;
    int m_minSeamen;			// Matrosen
    float m_maxSailSurface;
    QString m_file;
};

#endif
