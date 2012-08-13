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
#include <QtDebug>
#include "ohparameter.h"
#include <OQString>

#include "buildings/market.h"
#include "buildings/warehouse.h"
#include "buildings/workerhouse.h"


#include <QtCore/QXmlStreamAttributes>
#include <QtCore/QXmlStreamWriter>

City::City(const QString &cityname) : AbstractCity(cityname)
{
}

/*City::City(const City &other) :
 m_id (other.m_id),
 m_name (other.m_name),
 m_coordinates (other.m_coordinates),
 m_inhabitants (other.m_inhabitants),
 m_lifequality (other.m_lifequality),
 m_luxuryrate (other.m_luxuryrate),
 m_hasKontor (other.m_hasKontor),		//Kontor built in this town.
 m_storage (other.m_storage),
 m_production (other.m_production)
{
  //  m_buildings (other.m_buildings), 
  
}*/

void City::init()
{
  qWarning() << "void City::init()" << m_id;
  for(int i=0; i<const_warenanzahl; i++)
  {
    int r = rand()%20;
    int s = rand()%20;
    int p = rand()%10;
    m_storage.setGood(i, s + r + p);
  }
  m_inhabitants = 50 + rand()%100;				//das kommt mal noch ins XML-Zeugs rein
  Market *market = new Market();
  market->setState(1);
  market->pos().moveTo(500 + qrand() % 3000, 500 + qrand() % 3000);
  addBuilding(market);
  qWarning() << "Market added" << market->pos().size() << market->pos().topLeft() << market->pos();
  Warehouse *warehouse = new Warehouse();
  do
  {
//     qWarning() << warehouse->pos() << market->pos();
    warehouse->pos().moveTo(market->pos().x() + (qrand()%500) - 200, market->pos().y() + (qrand()%500) - 200);
  }
  while(warehouse->pos().intersects(market->pos()));
  addBuilding(warehouse);
  qWarning() << "Warehouse and market added." << warehouse->pos() ;
  QList<QRect>rectlist;
  rectlist << warehouse->pos() << market->pos();
  bool intersects(false);
  float factor (1);
  for(int i = m_inhabitants/50 + qrand()%3; i; i--)
  {
    qWarning() << "House: " << i << "added" << factor;
    WorkerHouse *house = new WorkerHouse();
    do
    {
      house->pos().moveTo(market->pos().x() + (qrand()%(int (500 * factor))) - 200, market->pos().y() + (qrand()%(int (500 * factor))) - 200);
      const QList<QRect>::const_iterator endit = rectlist.end();
      intersects = false;
      for(QList<QRect>::const_iterator it = rectlist.begin(); it != endit; ++it)
      {
	intersects = intersects | house->pos().intersects((*it));
      }
      factor += 0.05;
    }
    while(intersects);
    addBuilding(house);
    rectlist << house->pos();
    qWarning() << house->pos() << factor;
  }
  qWarning() << "EndOf City::init()";
}



void City::setStorage(const Goods &param_storage)
{
  m_storage = param_storage;
}

QString City::printGoods() const
{
  QString result;
  //   for(int i = 0; i<const_warenanzahl; i++)
  //   {
  // 		dbg = ;
  // 		OHDebug(QString("%1 ").arg(m_storage.good(i)).append(GAMEPARAMETER->GoodName(i)));
  //   }
  
  return result;
}

/*void City::production(int param_durchlauf)
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
/*
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
					currentLifeQuality -= (rand()%3 - m_storage.good(i));
					
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

}*/

QByteArray City::data() const
{
  QByteArray data;
  QXmlStreamWriter writer(&data);
  writer.writeStartElement("city");
  writer.writeAttributes(xmlAttributes());
  writer.writeEmptyElement("production");
  writer.writeAttributes(m_production.xmlAttributes());
  writer.writeEmptyElement("storage");
  writer.writeAttributes(m_storage.xmlAttributes());
  Building *bit;
  foreach(bit, m_Buildings)
  {
    writer.writeEmptyElement("building");
    writer.writeAttributes(bit->xmlAttributes());
  }
  writer.writeEndDocument();
  return data;
}

QXmlStreamAttributes City::xmlAttributes() const
{
  QXmlStreamAttributes list;
  
  list << QXmlStreamAttribute("id", QString::number(m_id));
  list << QXmlStreamAttribute("name", m_name);
  //  list << QXmlStreamAttribute("x-coordinate",	QString::number(m_coordinates.x()));
  //  list << QXmlStreamAttribute("y-coordinate",	QString::number(m_coordinates.y()));
  list << QXmlStreamAttribute("coordinates",	StringFromPoint(m_coordinates));
  list << QXmlStreamAttribute("inhabitants",	QString::number(m_inhabitants));
  list << QXmlStreamAttribute("growth",		QString::number(m_growth));
  list << QXmlStreamAttribute("lifequality",	QString::number(m_lifequality));
  list << QXmlStreamAttribute("luxuryrate",	QString::number(m_luxuryrate));
  list << QXmlStreamAttribute("education",	QString::number(m_education));
  list << QXmlStreamAttribute("beggars",	QString::number(m_beggars));
  list << QXmlStreamAttribute("richs",		QString::number(m_richs));
  list << QXmlStreamAttribute("wealths",	QString::number(m_wealths));
  list << QXmlStreamAttribute("poors",		QString::number(m_poors));
   
  return list;
}

void City::setXmlAttributes (const QXmlStreamAttributes &attributes)
{
  m_id =	attributes.value("id").toString().toInt();
  m_name =	attributes.value("name").toString();
  m_coordinates.setX(attributes.value("x-coordinate").toString().toInt());
  m_coordinates.setY(attributes.value("y-coordinate").toString().toInt());
  m_inhabitants = attributes.value("inhabitants").toString().toInt();
  m_growth =	attributes.value("growth").toString().toInt();
  m_lifequality = attributes.value("lifequality").toString().toInt();
  m_luxuryrate = attributes.value("luxuryrate").toString().toInt();
  m_education = attributes.value("education").toString().toInt();
  m_richs =	attributes.value("richs").toString().toInt();
  m_wealths =	attributes.value("wealths").toString().toInt();
  m_poors =	attributes.value("poors").toString().toInt();
  m_beggars =	attributes.value("beggars").toString().toInt();

//   m_ = attributes.value("").toString().toInt();

}


void City::addBuilding(Building *addb)
{
  m_Buildings[addb->id()] = addb;
}

void City::setCoordinates(const QPoint &coords)
{
  m_coordinates = coords;
}
