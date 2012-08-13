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

#ifndef _Time_h
#define _Time_h

#include <QtCore/QObject>

class Time : public QObject
{
  Q_OBJECT
  public:
    Time ();
    
    void refreshTime();
    
    void setMinute(const double &);
    void setHour(int);
    void setDay(int);
    void setMonth(int);
    void setYear(int);
    void setDayLength(int);
    
    double minute	() const	{	return m_minute;	}
    int hour		() const	{	return m_hour;		}
    int day		() const	{	return m_day;		}
    int month		() const	{	return m_month;		}
    int year		() const	{	return m_year;		}
    int dayLength	() const	{	return m_day_length;	}
    
  signals:
    void newDay(int);
    void newMonth(int);
    void newYear(int);
    
  private:
    int m_day_length;
    double m_minute;
    int m_hour;
    int m_day;
    int m_month;
    int m_year;
    
    bool m_leapyear;
    
};

#endif
