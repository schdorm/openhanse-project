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

#ifndef _OHLabels_H
#define _OHLabels_H

#include <QtCore/QObject>
#include <QtCore/QHash>

#define GoodLabel(x) goodName(x)
#define BuildingLabel(x) buildingName(x)

#define goodLabel(x) goodName(x)
#define buildingLabel(x) buildingName(x)


class OHLabels : public QObject	// inherited for the tr()-Function (translation)
{
  public:
    OHLabels();
    
    const QHash <int, QString> &GoodLabels	() const {	return m_GoodLabels;		}
    const QHash <int, QString> &BuildingLabels	() const { 	return m_BuildingLabels;	}
        
    QString goodName 	(int key) const {	return m_GoodLabels.value(key);		}
    QString buildingName(int key) const {	return m_BuildingLabels.value(key);	}

  private:
    
    QHash<int, QString> m_GoodLabels;
    QHash<int, QString> m_BuildingLabels;
    
};

#endif
