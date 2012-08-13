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

#ifndef _FACTORY_H
#define _FACTORY_H

#include <Building>
#include <Goods>

namespace Factory
{
  enum Factorytype
  {
    Woodchopperhut = Goods::Trunks + Building::Factory,
    Lumbermill = Goods::Shelves + Building::Factory,
    Oremine = Goods::IronOre + Building::Factory,
    Smeltery,
    Forge
  };
  
}

// class Factory : public Building
// {
// public:
//   
//   
//   
//   Factory(int);
// 
//   QByteArray description() const;
// 
//   private:
//     
//     
//   protected:
//     
// };

#endif
