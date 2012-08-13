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


#include "ohparameter.h"
#include <Goods>

#include "ohtime.h"

OHParameter::OHParameter() : m_time ( new Time)
{

m_GoodEnumList
<< Goods::Trunks
<< Goods::Shelves 
<< Goods::Charcoal 
<< Goods::Pitch 
<< Goods::Bricks
<< Goods::IronOre
<< Goods::MalleableIron 
<< Goods::Tools
<< Goods::Leather
<< Goods::Wool
<< Goods::Cloth 
<< Goods::Hemp

<< Goods::Beer
<< Goods::Cereal
<< Goods::Bread 
<< Goods::Salt
<< Goods::Meat 
<< Goods::Fish
<< Goods::Cheese
<< Goods::Wine 
<< Goods::Spicery
<< Goods::Gold 
<< Goods::Jewellery ;



m_GoodBasicPrices[Goods::Trunks] = 50;
m_GoodBasicPrices[Goods::Shelves] = 95;
m_GoodBasicPrices[Goods::Charcoal] = 84;
m_GoodBasicPrices[Goods::Pitch] = 67;
m_GoodBasicPrices[Goods::Bricks] = 10000;
m_GoodBasicPrices[Goods::IronOre] = 350;
m_GoodBasicPrices[Goods::MalleableIron] = 950;
m_GoodBasicPrices[Goods::Tools] = 168;
m_GoodBasicPrices[Goods::Leather] = 270;
m_GoodBasicPrices[Goods::Wool] = 400;
m_GoodBasicPrices[Goods::Cloth] = 107;
m_GoodBasicPrices[Goods::Hemp] = 60;

m_GoodBasicPrices[Goods::Beer] = 50;
m_GoodBasicPrices[Goods::Cereal] = 1;
m_GoodBasicPrices[Goods::Bread] = 1;
m_GoodBasicPrices[Goods::Salt] = 1;
m_GoodBasicPrices[Goods::Meat] = 300;
m_GoodBasicPrices[Goods::Fish] = 190;
m_GoodBasicPrices[Goods::Cheese] = 90;
m_GoodBasicPrices[Goods::Wine] = 420;
m_GoodBasicPrices[Goods::Spicery] = 1000;
m_GoodBasicPrices[Goods::Gold] = 2000;
m_GoodBasicPrices[Goods::Jewellery] = 4000;
// m_GoodBasicPrices[Goods::] = ;
// m_GoodBasicPrices[Goods::] = ;

}

OHParameter::~OHParameter()
{
  delete m_time;
}

void OHParameter::setGameSpeed(int speed)
{
  m_GameSpeed = speed;
}
void OHParameter::setGameDifficulty(int difficulty)
{
  m_GameDifficulty = difficulty;
}

/*void OHParameter::setFirstName	(const QString &firstName)
{
  m_FirstName = firstName;
}

void OHParameter::setLastName	(const QString &lastName )
{
  m_LastName = lastName;
}*/

