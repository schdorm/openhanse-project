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

#include "ohtime.h"

Time::Time() :
 m_day_length ( 2000),
 m_minute ( 0 ),
 m_hour ( 12 ),
 m_day ( 1 ),
 m_month ( 4 ),
 m_year ( 1350 )
{

}


void Time::setDayLength(int dlparam)
{
	m_day_length = dlparam;
}

void Time::setMinute(const double &min)
{
	m_minute = min;
}

void Time::setHour(int hr_param)
{
	m_hour = hr_param;
}

void Time::setDay(int dayparam)
{
	m_day = dayparam;
}

void Time::setMonth(int monthparam)
{
	m_month = monthparam;
}

void Time::setYear(int yearparam)
{
	m_year = yearparam;
}

void Time::refreshTime()		//bool -> new Day ?
{
  m_minute += m_day_length/1440;		// day has 24*60 = 1440 minutes
  if(m_minute>=60)
  {
	m_minute = 0;
	m_hour ++;
	if(m_hour >=24)
	{
		m_day++;
		m_hour = 0;
// 		emit newDay(m_day);
		
		switch(m_month)
		{
		  case 2:
		  {
		    if((m_day > 28 && ! m_leapyear) || m_day > 29)
		    {
		      m_day = 1;
		      m_month++;
		      emit newMonth(m_month);
		      break;
		    }
		  }
		  case 1:
		  case 3:
		  case 5:
		  case 7:
		  case 8:
		  case 10:
		  case 12:
		    if(m_day < 32)
		      break;
		  default:
		    if(m_day < 31)
		      break;
		    else
		    {
		      m_day = 1;
		      m_month++;
		      if(m_month > 12)
		      {
			m_month = 1;
			m_year ++;
			if(m_year%4 == 0 && m_year%100 != 0)
			{
			  m_leapyear = true;
			}
			else
			  m_leapyear = false;
			emit newYear(m_year);
		      }
		      else
			emit newMonth(m_month);
		      break;
		    }
		}
		
		/*if((m_day > 31 && (m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10 || m_month == 12)) ||
		(m_day > 30 && ( m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)) ||
		(m_month == 2 && ((m_day > 28 && (m_year%4 != 0 || m_year%100 == 0)) || (m_day > 29 && m_year%4 == 0))))
		{
			m_day = 1;
			m_month++;
		}*/
		emit newDay(m_day);		//new day is rising
	}
  }
//   return ;				// still the old day ...
}

