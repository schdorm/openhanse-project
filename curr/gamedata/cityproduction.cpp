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

#include "city.h"
// #include <QtDebug>
// #include "ohparameter.h"
// #include <OQString>


void City::production(int param_durchlauf)
{
  
  const QHash<int, int> prodhash = AbstractCity::production().goods();
  QList <int> m_hproductionlist;
  QList <int> m_mproductionlist;
  QList <int> m_lproductionlist;
  //   int it;
  //   foreach(it, prodhash.keys())
  QHash<int, int>::const_iterator it;
  const QHash<int, int>::const_iterator endit = prodhash.end();
  for(it = prodhash.begin(); it != endit; ++it)
  {
    switch(it.value())
    {
      case Goods::LowProduction:
      {
	m_lproductionlist << it.key();
	break;
      }
      case Goods::NormalProduction:
      {
	m_mproductionlist << it.key();
	break;
      }
      case Goods::HighProduction:
      {
	m_hproductionlist << it.key()
	;
	break;
      }
      default:
	break;
    }
  }
  /*
  next generation:
  m_storage[Goods::Beer] += m_inhabitants/25 * m_production[Goods::Beer] / 10;
  m_storage[Goods::Cereal] -= m_inhabitants/50 * m_production[Goods::Beer] / 10;
  */

// 		qWarning() << "Stadtproduktion:" << m_name;

		for(QList<int>::iterator it = m_hproductionlist.begin(); it != m_hproductionlist.end(); ++it)
		{
// 			switch(m_hproduction[j])
			switch(*it)
			{
			case Goods::Trunks:			//Baumstaemme
				{
				m_storage.addGood(Goods::Trunks, 1);		//Grundproduktion um Festfahren und komplette Stockung der Wirtschaft zu verhindern
				
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
				if(m_storage.good(Goods::Tools) - m_inhabitants/250 > 0)
				{
				m_storage.setGood(Goods::Trunks, m_storage.good(Goods::Trunks) + m_inhabitants/40);
				m_storage.setGood(Goods::Tools, m_storage.good(Goods::Tools) - m_inhabitants/250);
				}

				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/100 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/200 > 0)
				{
				m_storage.addGood(Goods::Shelves, m_inhabitants/40);
				m_storage.addGood(Goods::Trunks, - m_inhabitants/100);
				m_storage.addGood(Goods::Tools, - m_inhabitants/200);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/300 > 0 && m_storage.good(Goods::Shelves) - 1 > 0 )
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/150);
				m_storage.addGood(Goods::Trunks, - m_inhabitants/300);
// 				m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Pitch:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/500 > 0 &&
 				m_storage.good(Goods::Shelves) - 1 > 0)
				{
					m_storage.addGood(Goods::Pitch,  m_inhabitants/80);
					m_storage.addGood(Goods::Trunks, - m_inhabitants/500);
					m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Bricks:				//Steine / Ziegel
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/500 > 0)
				{
					m_storage.addGood(Goods::Bricks, m_inhabitants/100);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/800);
					m_storage.addGood(Goods::Tools, - m_inhabitants/300);
				}
				break;
				}
			case Goods::IronOre:			//Eisenerz
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/400 >0)
				{
					m_storage.addGood(Goods::IronOre, m_inhabitants/100);
					m_storage.addGood(Goods::Tools, - m_inhabitants/400);
				}
				m_storage.addGood(Goods::IronOre, +1);	// Grundproduktion
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(Goods::IronOre) - m_inhabitants/100 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/300 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/500 > 0)
				{
					m_storage.addGood(Goods::MalleableIron, m_inhabitants/150);
					m_storage.addGood(Goods::IronOre, - m_inhabitants/140);	
					m_storage.addGood(Goods::Charcoal, - m_inhabitants/300);
					m_storage.addGood(Goods::Tools, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(Goods::MalleableIron) - m_inhabitants/200 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/500 > 0 && m_storage.good(Goods::Shelves) - m_inhabitants/400 > 0)
				{
					m_storage.addGood(Goods::Tools, m_inhabitants/25);
					m_storage.addGood(Goods::MalleableIron, - m_inhabitants/200);
					m_storage.addGood(Goods::Charcoal, -- m_inhabitants/500);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/400);
				}
				m_storage.addGood(Goods::Tools, 1);
				break;
				}
			case Goods::Leather:			//Leder
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/700 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/700 > 0)
				{
					m_storage.addGood(Goods::Leather,  m_inhabitants/100);
					m_storage.addGood(Goods::Salt, - m_inhabitants/700);
					m_storage.addGood(Goods::Tools, - m_inhabitants/700);
				}
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/600 > 0 && m_storage.good(Goods::Cereal) - m_inhabitants/600 > 0)
				{
					m_storage.addGood(Goods::Wool,  m_inhabitants/200);
					m_storage.addGood(Goods::Tools, --m_inhabitants/600);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/600);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				if(m_storage.good(Goods::Wool) - m_inhabitants/500 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Cloth, m_inhabitants/80);
					m_storage.addGood(Goods::Wool, - m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/800 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Salt, m_inhabitants/80);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/800);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/100 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/400 > 0 && m_storage.good(Goods::Hemp) - m_inhabitants/250 > 0)
				{
					m_storage.addGood(Goods::Fish,  m_inhabitants/30);
					m_storage.addGood(Goods::Salt, - m_inhabitants/100);
					m_storage.addGood(Goods::Tools, - m_inhabitants/400);
					m_storage.addGood(Goods::Hemp, - m_inhabitants/250);
				}
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/200 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Salt) - m_inhabitants/300 > 0)
				{
					m_storage.addGood(Goods::Meat,  m_inhabitants/45);
					m_storage.addGood(Goods::Tools, - m_inhabitants/250);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/100);
					m_storage.addGood(Goods::Salt, - m_inhabitants/100);
				}
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Cereal, m_inhabitants/10);
					m_storage.addGood(Goods::Tools, - m_inhabitants/100);
				}
				m_storage.addGood(Goods::Cereal, 1);
				break;
				}
			case Goods::Beer:		//Bier
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/500 > 0 &&
				m_storage.good(Goods::Shelves) - m_inhabitants/1000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Beer,  m_inhabitants/25);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/100);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/200);
					m_storage.addGood(Goods::Tools, - m_inhabitants/200);
				}
				break;
				}
			case Goods::Wine:		//Wein
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Wine, m_inhabitants/50);
					m_storage.addGood(Goods::Tools, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Hemp:		//Hanf
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Hemp,  m_inhabitants/250);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
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
		
		for(QList<int>::iterator it = m_mproductionlist.begin(); it != m_mproductionlist.end(); ++it)
		{
			switch(*it)
			{
			case Goods::Trunks:			//Baumstaemme
				{
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.setGood(Goods::Trunks, m_storage.good(Goods::Trunks) + m_inhabitants/200);
					m_storage.setGood(Goods::Tools, m_storage.good(Goods::Tools) - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/400 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/800 > 0)
				{
				m_storage.addGood(Goods::Shelves, m_inhabitants/200);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/400);
				m_storage.addGood(Goods::Tools, - m_inhabitants/800);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Shelves) - 1 > 0 )
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/800);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1000);
// 				m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Pitch:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1000 > 0 &&
 				m_storage.good(Goods::Shelves) - 1 > 0)
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/200);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Bricks:			//Steine / Ziegel
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/800 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1500 > 0)
				m_storage.addGood(Goods::Bricks, m_inhabitants/800);
				m_storage.addGood(Goods::Shelves, - m_inhabitants/1500);
				m_storage.addGood(Goods::Tools, - m_inhabitants/800);
				break;
				}
			case Goods::IronOre:
				{		//Eisenerz
				if(m_storage.good(Goods::Tools) - m_inhabitants/800 >0)
				{
				m_storage.addGood(Goods::IronOre, m_inhabitants/400);
				m_storage.addGood(Goods::Tools, - m_inhabitants/800);
				}
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(Goods::IronOre) - m_inhabitants/400 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/800 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
				m_storage.addGood(Goods::MalleableIron, m_inhabitants/500);
				m_storage.addGood(Goods::IronOre, - m_inhabitants/400);	
				m_storage.addGood(Goods::Charcoal, - m_inhabitants/800);
				m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(Goods::MalleableIron) - m_inhabitants/400 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Shelves) - m_inhabitants/800 > 0)
				{
					m_storage.addGood(Goods::Tools, m_inhabitants/40);
					m_storage.addGood(Goods::MalleableIron,  m_inhabitants/400);
					m_storage.addGood(Goods::Charcoal, - m_inhabitants/1000);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/800);
				}
				m_storage.addGood(Goods::Tools, 1);
				break;
				}
			case Goods::Leather:			//Leder
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Leather,  m_inhabitants/1000);
					m_storage.addGood(Goods::Salt, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Wool,  m_inhabitants/1000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				if(m_storage.good(Goods::Wool) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cloth, m_inhabitants/100);
					m_storage.addGood(Goods::Wool, - m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/1600 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Salt, m_inhabitants/100);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/1600);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/400 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Fish,  m_inhabitants/400);
					m_storage.addGood(Goods::Salt, - m_inhabitants/400);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/400 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Salt) - m_inhabitants/500 > 0)
				{
					m_storage.addGood(Goods::Meat,  m_inhabitants/400);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/400);
					m_storage.addGood(Goods::Salt, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cereal, m_inhabitants/120);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				m_storage.addGood(Goods::Cereal, 1);
				break;
				}
			case Goods::Beer:		//Bier
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/1000 > 0 &&
				m_storage.good(Goods::Shelves) - m_inhabitants/2000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Beer,  m_inhabitants/200);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/1000);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wine:		//Wein
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
				m_storage.addGood(Goods::Wine, m_inhabitants/500);
				m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
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
			case Goods::Hemp:		//Hanf?
				{
				break;
				}

			default:
				break;
			}
		}
		for(QList<int>::iterator it = m_lproductionlist.begin(); it != m_lproductionlist.end(); ++it)
		{
			switch(*it)
			{
			case Goods::Trunks:			//Baumstaemme
				{
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
				if(m_storage.good(Goods::Tools) - m_inhabitants/1500 > 0)
				{
				m_storage.setGood(Goods::Trunks, m_storage.good(Goods::Trunks) + m_inhabitants/250);
				m_storage.setGood(Goods::Tools, m_storage.good(Goods::Tools) - m_inhabitants/1500);
				}
				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/500 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
				m_storage.addGood(Goods::Shelves,m_inhabitants/250);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/500);
				m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1500 > 0 && m_storage.good(Goods::Shelves) - 1 > 0 )
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/1000);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1500);
// 				m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, 1);
				}
				break;
				}
			case Goods::Pitch:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1500 > 0 &&
 				m_storage.good(Goods::Shelves) - 1 > 0)
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/250);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1500);
				m_storage.addGood(Goods::Shelves, 1);
				}
				break;
				}
			case Goods::Bricks:			//Steine / Ziegel
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/1500 > 0 )
				{
				m_storage.addGood(Goods::Bricks, m_inhabitants/800);
				m_storage.addGood(Goods::Shelves, - m_inhabitants/1500);
// 				m_storage.good(Goods::Shelves) --;
				}
				break;
				}
			case Goods::IronOre:
				{		//Eisenerz
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 >0)
				{
				m_storage.addGood(Goods::IronOre, m_inhabitants/1000);
				m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(Goods::IronOre) - m_inhabitants/800 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/1200 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1500 > 0)
				{
				m_storage.addGood(Goods::MalleableIron, m_inhabitants/1000);
				m_storage.addGood(Goods::IronOre, - m_inhabitants/800);	
				m_storage.addGood(Goods::Charcoal, - m_inhabitants/1200);
				m_storage.addGood(Goods::Tools, - m_inhabitants/1500);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(Goods::MalleableIron) - m_inhabitants/500 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/1500 > 0 && m_storage.good(Goods::Shelves) - m_inhabitants/1200 > 0)
				{
					m_storage.addGood(Goods::Tools, m_inhabitants/100);
					m_storage.addGood(Goods::MalleableIron,  m_inhabitants/500);
					m_storage.addGood(Goods::Charcoal, - m_inhabitants/1500);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/1200);
				}
				break;
				}
			case Goods::Leather:			//Leder
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Leather,  m_inhabitants/1000);
					m_storage.addGood(Goods::Salt, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Wool,  m_inhabitants/1500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				if(m_storage.good(Goods::Cloth) - m_inhabitants/1500 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cloth, m_inhabitants/250);
					m_storage.addGood(Goods::Wool, - m_inhabitants/1500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/2000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Salt, m_inhabitants/400);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/500 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Fish,  m_inhabitants/500);
					m_storage.addGood(Goods::Salt, - m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Salt) - m_inhabitants/500)
				{
					m_storage.addGood(Goods::Meat,  m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/1000);
					m_storage.addGood(Goods::Salt, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cereal, m_inhabitants/250);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Beer:		//Bier
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/1500 > 0 &&
				m_storage.good(Goods::Shelves) - m_inhabitants/2000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Beer,  m_inhabitants/250);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/1500);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wine:		//Wein
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
				m_storage.addGood(Goods::Wine, m_inhabitants/1000);
				m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
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
			case Goods::Hemp:		//Hanf?
				{
				break;
				}

			default:
				break;
			}
		}
// 			if(hproduction[j) == i)
// 			{
// 			qWarning() << "Hproduktion vorher: "<< m_storage.good(i);
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
// 			qWarning() << "Hproduktion nachher" << m_storage.good(i);
// 			}
// 			if(mproduction[j) == i)
// 			{
// 			qWarning() << "MProduktion vorher" << m_storage.good(i);
// 			m_storage.good(i) += ((rand() % 9) + m_inhabitants/200);
// 			qWarning() << "MProduktion nachher" << m_storage.good(i);
// 			}
// 			if(lproduction[j) == i)
// 			{
// 			qWarning() << "NProduktion vorher" << m_storage.good(i);
// 			m_storage.good(i) += ((rand()% 4) + m_inhabitants/350);
// 			qWarning() << "NProduktion nachher" << m_storage.good(i);
// 			}
///////////////////Stadtverbrauch durch Essen ^^


		if(param_durchlauf%3==0)				//Alle 3 "Tage"
		{
			// stadtware[Goods::Trunks);
			m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
// stadtware[Goods::Charcoal) -= m_inhabitants/1000);		//Als Heizzeug .. evtl. anpassen
// stadtware[Goods::Pitch);
			m_storage.addGood(Goods::Bricks, -m_inhabitants/2000);
// stadtware[Goods::IronOre);
			m_storage.addGood(Goods::MalleableIron,  m_inhabitants/2000);
			m_storage.addGood(Goods::Tools, - m_inhabitants/500);
			m_storage.addGood(Goods::Leather, - m_inhabitants/500);		//Leder
			m_storage.addGood(Goods::Wool, - m_inhabitants/1000);
			m_storage.addGood(Goods::Cloth, - m_inhabitants/300);
			m_storage.addGood(Goods::Salt, - m_inhabitants/500);
			m_storage.addGood(Goods::Fish, - m_inhabitants/100);
					//Fisch hauefig gegessen
			m_storage.addGood(Goods::Meat, - m_inhabitants/800);
					//Fleisch fuer wohlhabendere Schichten
			m_storage.addGood(Goods::Cereal, - m_inhabitants/100);
					//Getreide fuer alle
			m_storage.addGood(Goods::Bread, - m_inhabitants/60);
					//Brot als Grundnahrungsmittel überhaupt fuer alle	
			m_storage.addGood(Goods::Beer, - m_inhabitants/50);
					//Bier auch sehr wichtig - billiges Getraenk fuer jedermann
			m_storage.addGood(Goods::Wine, - m_inhabitants/100);
					//Wein wieder fuer wohlhabendere Schichten
// stadtware[17];
// stadtware[18];
// stadtware[19];
			int currentLifeQuality = 0;

			for(int i = 0; i < const_warenanzahl ;i++)
			{
				if(m_storage.good(i) < 0)
				{
					currentLifeQuality -= (qrand()%3 - m_storage.good(i));
					
					// m_storage.good(i) is negative -> adds a positive value to the rand-value -> -= value
					
					m_storage.setGood(i, 0);
					
				
				}
				else
				{
					currentLifeQuality ++;
				}
			}
			currentLifeQuality = m_lifequality + 4*currentLifeQuality;
			currentLifeQuality = currentLifeQuality / 5;
			m_lifequality = currentLifeQuality;
			m_inhabitants += currentLifeQuality;
// 			qWarning() << "current Inhabitants:" << m_inhabitants << "(" << currentLifeQuality << ")";
		}

// 		for (QList<stadtklasse>::iterator it = stadtliste.begin(); it != stadtliste.end(); ++it)
// 		{
// // 			qWarning() << it->stadtname << hf->mapprops.stadtname ;
// 			if(it->stadtname == stadtname)
// 			{
// 				*it = stadt;
// 				break;
// 			}
// 		}

}
