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
#ifndef _OHParameter_h
#define _OHParameter_h

#include <QtCore/QHash>

class Time;

class OHParameter
{
  public:
    OHParameter();
    ~OHParameter();
    
    int gameDifficulty			()	const	{	return m_GameDifficulty;		}
    int gameSpeed			()	const	{	return m_GameSpeed;			}
    int basicPrice		 (int key)	const	{	return m_GoodBasicPrices.value(key);	}
    const QList<int> &goodEnums		()	const	{	return m_GoodEnumList;			}
    
    const QHash <int, int> &GoodBasicPrices ()	const 	{	return m_GoodBasicPrices;		}
    
    void setGameSpeed(int);
    void setGameDifficulty(int);
    
    Time *time() { return m_time;}
    const Time * time() const { return m_time; }
    
    //     const QString &firstName		()	const	{	return m_FirstName;		}
    //     const QString &lastName		()	const	{	return m_LastName;		}
    //     QString m_FirstName;		//Players first /
    //     QString m_LastName;			// last name
    //     void setFirstName	(const QString &firstName);
    //     void setLastName	(const QString &lastName );

    
  private:
    
    int m_GameSpeed;
    int m_GameDifficulty;
    
    QHash<int, int> m_GoodBasicPrices;
    
    
    QList<int> m_GoodEnumList;
    Time *m_time;
};

#endif
