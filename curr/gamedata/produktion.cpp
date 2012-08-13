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

#include "dataclass.h"
// #include "gesamtbild.h"
#include "goods.h"
#include "city.h"
#include "kontor.h"
#include <QtDebug>


void DataClass::produktion(int durchlauf)
{
// 	QList <City*> cityList = GAMEDATA->ret_CityList();
	City *cityit = 0;
	foreach(cityit, m_CityList)
	{
		cityit->production(durchlauf);
	}
	
// 	for(QList<City*>::iterator it = m_CityList.begin(); it != m_CityList.end(); ++it)
// 	{
// 		it->production(durchlauf);
// 	}
}
