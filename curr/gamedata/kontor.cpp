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

#include "kontor.h"

Kontor::Kontor() : Building( Building::Kontor )
{
// 	static int idzaehler;
// 	m_kontorid = idzaehler;
// 	idzaehler++;

// 	for(int i=0; i< const_warenanzahl; i++)
// 	{
// 		m_storage.setGood(i, 0);
// 		m_production.setGood(i, 0);
// 	}

	m_storage.setCapacity(800);
// 	m_storage.setFilling(0);
// 	m_storage.setTaler (0);
// 	m_storage.setExchangeVolume(0);
// 	m_production.setTaler(0);
}

QByteArray Kontor::description() const
{
  return "";
}

void Kontor::productGoods()
{
QHash<int, double> production_param;

	for(int i = 0; i<const_warenanzahl; i++)
	{
		production_param[i] = -1;
	}
	
	for(int i = 0; i < const_warenanzahl; i++)
	{
		if(m_production.good(i) < 0)
		{
		    if(m_storage.good(i) < m_production.good(i))
// 		    {
// 			m_storage.addGood(i, m_production.good(i));
// 		    }
// 		    else
		    {
			switch(i)
			{
			case Goods::Trunks:			//Baumstaemme
				{
				production_param[Goods::Pitch] = m_storage.good(i) / m_production.good(i);
				production_param[Goods::Charcoal] = m_storage.good(i) / m_production.good(i);
				production_param[Goods::Salt] = m_storage.good(i) / m_production.good(i);
				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Salt])
				{
					production_param[Goods::Salt] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Bricks])
				{
					production_param[Goods::Bricks] = m_storage.good(i) / m_production.good(i);
				}
				
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Charcoal])
				{
					production_param[Goods::Charcoal] = m_storage.good(i) / m_production.good(i);
				}
				
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Pitch])
				{
					production_param[Goods::Pitch] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Tools])
				{
					production_param[Goods::Tools] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Beer])
				{
					production_param[Goods::Beer] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Tools])
				{
					production_param[Goods::Tools] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::MalleableIron])
				{
					production_param[Goods::MalleableIron] = m_storage.good(i) / m_production.good(i);
				}
				
				break;
				}
			case Goods::Pitch:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				
				break;
				}
			case Goods::Bricks:				//Steine / Ziegel
				{
				
				break;
				}
			case Goods::IronOre:			//Eisenerz
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::MalleableIron])
				{
					production_param[Goods::MalleableIron] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Tools])
				{
					production_param[Goods::Tools] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Trunks])
				{
					production_param[Goods::Trunks] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Shelves])
				{
					production_param[Goods::Shelves] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::IronOre])
				{
					production_param[Goods::IronOre] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Cloth])
				{
					production_param[Goods::Cloth] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Wine])
				{
					production_param[Goods::Wine] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Fish])
				{
					production_param[Goods::Fish] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Beer])
				{
					production_param[Goods::Beer] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Meat])
				{
					production_param[Goods::Meat] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Leather])
				{
					production_param[Goods::Leather] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Cereal])
				{
					production_param[Goods::Cereal] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::MalleableIron])
				{
					production_param[Goods::MalleableIron] = m_storage.good(i) / m_production.good(i);
				}
				
				break;
				}
			case Goods::Leather:			//Leder
				{
				
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Cloth])
				{
					production_param[Goods::Cloth] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Leather])
				{
					production_param[Goods::Leather] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Meat])
				{
					production_param[Goods::Meat] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Fish])
				{
					production_param[Goods::Fish] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Leather])
				{
					production_param[Goods::Leather] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Meat])
				{
					production_param[Goods::Meat] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Beer])
				{
					production_param[Goods::Beer] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Wool])
				{
					production_param[Goods::Wool] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Beer:		//Bier
				{
				break;
				}
			case Goods::Wine:		//Wein
				{
				break;
				}
			case Goods::Hemp:		//Hanf
				{
				break;
				}
			case Goods::Gold:		//Gold
				{
				break;
				}
			case Goods::Jewellery:		//Schmuck
				{
				break;
				}
			default:
				break;
			}
			}
		    }
		
		    
	}
for(int i = 0; i < const_warenanzahl; i++)
{
m_storage.addGood(i, - m_production.good(i) * production_param.value(i));		// neg. production_param * neg prod = pos nettoprod. --> -nettoprod = neg. ; neg prod_param * pos prod = neg. nettoproduction --> -nettoprod = pos 
}
}
