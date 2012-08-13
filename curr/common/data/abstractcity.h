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

#ifndef _AbstractCity_H
#define _AbstractCity_H

#include <QtCore/QString>
#include <QtCore/QObject>


#include "goods.h"
//   #define DEBUG_CITY


class QXmlStreamAttributes;

class AbstractCity : public QObject
{
  public:
    #ifdef DEBUG_CITY
    ~AbstractCity();
    //AbstractCity(const QXmlStreamAttributes &attributes);
    #endif
    
    AbstractCity(const QString & = 0, QObject * = 0);

    //     AbstractCity(const AbstractCity &other);
    
    void setID			(int);
    void setName		(const QString &);
    void setProduction		(int, const QString&);
    
    
    int id 			() const	{	return m_id;		}
    QString name		() const	{	return m_name;		}
    // const QString &nameref	() const	{	return m_name;		}
    
    // returns production-things 
    const Goods &production	() const	{	return m_production;		}
    Goods &production 		() 		{	return m_production;		}
    
    AbstractCity &operator=(const AbstractCity&);
    
    virtual QXmlStreamAttributes xmlAttributes () const;
    virtual void setXmlAttributes(const QXmlStreamAttributes &);
    
  protected:
    int m_id;
    QString m_name;
    Goods m_production;
    
  private:
    
    #ifdef DEBUG_CITY
    static int M_citycounter;
    #endif
    
};


#endif

