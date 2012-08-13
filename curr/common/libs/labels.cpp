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

#include "libs/labels.h"
#include "data/goods.h"
#include "data/building.h"

OHLabels::OHLabels()
{
  // GoodLabels.insert();
  m_GoodLabels.insert(Goods::Trunks, tr("trunks"));		//Baumstaemme
  m_GoodLabels.insert(Goods::Shelves,tr("shelves"));		//Holzbretter
  m_GoodLabels.insert(Goods::Charcoal, tr("charcoal"));		//Holzkohle
  m_GoodLabels.insert(Goods::Pitch, tr("pitch"));			//Pech
  m_GoodLabels.insert(Goods::Bricks, tr("bricks"));		//Steine/Ziegel
  m_GoodLabels.insert(Goods::IronOre, tr("iron ore"));		//Eisenerz
  m_GoodLabels.insert(Goods::MalleableIron, tr("malleable iron"));	//Schmiedeeisen
  m_GoodLabels.insert(Goods::Tools, tr("tools"));			//Werkzeuge
  m_GoodLabels.insert(Goods::Leather, tr("leather"));		//Leder
  m_GoodLabels.insert(Goods::Wool, tr("wool"));			//Wolle
  m_GoodLabels.insert(Goods::Cloth, tr("cloth"));			//Stoff
  m_GoodLabels.insert(Goods::Hemp, tr("hemp"));			//Hanf
  
  m_GoodLabels.insert(Goods::Beer, tr("beer"));			//Bier
  m_GoodLabels.insert(Goods::Cereal, tr("cereal"));		//Getreide
  m_GoodLabels.insert(Goods::Bread, tr("bread"));			//Brot
  m_GoodLabels.insert(Goods::Salt, tr("salt"));			//Salz
  m_GoodLabels.insert(Goods::Meat, tr("meat"));			//Fleisch
  m_GoodLabels.insert(Goods::Fish, tr("fish"));			//Fisch
  m_GoodLabels.insert(Goods::Cheese, tr("cheese"));		//Kaese
  m_GoodLabels.insert(Goods::Wine, tr("wine"));			//Wein
  m_GoodLabels.insert(Goods::Spicery, tr("spicery"));		//Gewuerze
  m_GoodLabels.insert(Goods::Gold, tr("gold"));			//Gold
  m_GoodLabels.insert(Goods::Jewellery, tr("jewellery"));	//Schmuck
  
  
  
  m_BuildingLabels[Building::Factory] = tr("Factory");		// Werkstatt / Productionsgebäude
  m_BuildingLabels[Building::Townhall] = tr("Townhall");	// Rathaus
  // m_BuildingLabels[]
  
  m_BuildingLabels.insert(Building::Market, tr("Market"));	// Markt
  m_BuildingLabels.insert(Building::Church, tr("Church"));	// Kirche
  m_BuildingLabels.insert(Building::Port, tr("Port"));		// Hafen
  m_BuildingLabels.insert(Building::Kontor, tr("Kontor"));	// Kontor
  m_BuildingLabels.insert(Building::Bank, tr(""));
  m_BuildingLabels.insert(Building::Tavern, tr("Tavern"));	// Taverne, Kneipe, etc.
}
