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

#ifndef _KONTOR_H
#define _KONTOR_H

#include <Goods>
#include <Building>

class Kontor : public Building
{
  public:
    
    Kontor();
    
    // int getID()	const	{	return m_kontorid;	}
    // int cityID()	const	{	return m_CityID;		}
    
    // const Warenstruct &storage ()	const	{	return m_storage;	}
    
    const Goods &storage	()	const 	{	return m_storage;	}
    
    void productGoods();
    
    void setStorage(const Goods &param_storage)
    {
      m_storage = param_storage;
    }
    
    QByteArray description() const;
    
    // void build(const QString &param_cityname, int param_cityid)
    // {
      // 	m_CityName = param_cityname;
      // 	m_CityID = param_cityid;
      // 	m_TaxLevel = Tax::midhighLevel;
      // }
      
 private:
   Goods m_storage;
   Goods m_production;
};


#endif
