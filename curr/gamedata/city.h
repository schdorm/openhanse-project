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
#ifndef _City_h
#define _City_h

#include <Goods>
#include <AbstractCity>
// #include "building.h"

#include <QtCore/QPoint>

class QXmlStreamAttributes;
class Building;

class City : public AbstractCity
{
  Q_OBJECT
  public:
    
    /*enum
    {
      null = 0,
      NoProduction = 0,
      LowProduction = 1,		// 3		-- 186,67% of low production needed for normal demand
      NormalProduction = 2,		// 7		-- goods demand requires 80% of normal Production	
      HighProduction = 3,		// 10		-- 56 % of high production needed for normal demand
};*/
    
    
    //#CityClass(int = -1, const QString &, const QList<int> &,  const QList<int> &, const QList<int> &);
    // City( const QString &, const QList<int> &,  const QList<int> &, const QList<int> &, int = -1);
    City(const QString & = 0);
    // City(const City &);
    
    void init();
    
    
    QString printGoods		() const;
    
    void production		(int);				//--> produktion.cpp
    void setStorage		(const Goods &);
    
    
    // int id 			() const	{	return m_id;		}
    /// const QPoint &coordinates () const	{	return m_coordinates;	}
    
    
    int inhabitants	() const	{	return m_inhabitants;	}
    int beggars		() const	{	return m_beggars;	}
    int poors		() const	{	return m_poors;		}
    int wealths		() const	{	return m_wealths;	}
    int richs		() const	{	return m_richs;		}
    
    int growth		() const 	{	return m_growth;	}
    int education	() const 	{	return m_education;	}
    int lifequality	() const	{	return m_lifequality;	}
    int luxuryrate	() const	{	return m_luxuryrate;	} 
    
    void addBuilding(Building *);
    
    const Goods &storage	() const	{	return m_storage;	}	// returns store-good-amounts
    
    
    
    void setCoordinates(const QPoint &);
    const QPoint &coordinates() { return m_coordinates;	}
    
    QXmlStreamAttributes xmlAttributes () const;
    void setXmlAttributes(const QXmlStreamAttributes &);
    QByteArray data() const;
    
  private:
    QPoint m_coordinates;
    
    int m_inhabitants;
    
    int m_poors;
    int m_wealths;		// == people, who're well-of.
    int m_richs;
    
    /*
    population-structure:
    
    poor inhabitants	74 %		37 :
    wealthy inhabitants	22 %		11 :
    rich inhabitants	4 %		2
    
    growth >> new inhabitants >> beggars
    may get work from the city by coincidence >> poor inhabitants
    high lifequality >> wealths
    high luxuryrate >> richs
    */
    
    int m_growth;
    int m_lifequality;		// determines the growth/diminution of the city
    int m_luxuryrate;		// determines the percentage of the upper-class-inhabitants ( poor <--> rich)
    
    int m_education; // coming later ...
    /* effects on education:
    ++++	university (very expensive)	* # °
    +++	libary	(expensive)		*
    ++	1st. school (each additional school +)
    ++	lone monastery (in hinterland)	  #
    +	city-monastery			* #
    +	high trading activities		 (#)
    
    + >> rate of education
    
    * >> max. 1 per city
    # >> not buildable (self-development), support possible
    ° >> 4 schools needed for an university, one school turns into university
    
    higher education makes the city develop faster --> growth + prosperity
    */
    
    
    
    
    int m_beggars;		// non-poor/wealthy/rich inhabitants, unemployed population
    
    QHash <int, Building *> m_Buildings;
    
    Goods m_storage;
    
    // public slots:
    //  void produktion(int);
    
    // void produktion();
    // void verbrauch();
    
};


#endif

