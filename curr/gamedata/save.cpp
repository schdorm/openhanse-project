/***************************************************************************
 *   Copyright (C) 2009  - 2010 by Christian Doerffel                      *
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

#include "gamedata.h"


#include "ohtime.h"
#include "ship.h"
#include "city.h"

#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>
#include <QtDebug>

#include <QCoreApplication>


#include <QtCore/QFile>
#include <QtCore/QDir>

#include <OQString>



void GameData::save(QString save_filename, const QPoint &currentCoordinates) const
{
  if(!save_filename.endsWith(".ohs"))
  {
    save_filename.append(".ohs");
  }
  QFile savefile(save_filename.prepend("save/").prepend(QDir::currentPath()));
  savefile.open(QIODevice::WriteOnly);
  
  QByteArray saveArray;
  save(&saveArray);
  
  savefile.write(saveArray);
  
  savefile.close();
  qWarning() << "Nach " << save_filename << "gespeichert.";
}

void GameData::save(QByteArray *saveData) const
{
  if(saveData == 0)
  {
    return;
  }
	QXmlStreamWriter savexw(saveData);
	savexw.setAutoFormatting (true);
	savexw.writeStartDocument();
	savexw.writeStartElement("savefile");
	
	savexw.writeAttribute(QXmlStreamAttribute("version", qApp->applicationVersion()));
	savexw.writeAttribute(QXmlStreamAttribute("severity", QString::number(m_parameters.gameDifficulty())));
	
	savexw.writeStartElement("current-states");
	savexw.writeAttribute(QXmlStreamAttribute("cycle", QString("%1").arg(m_cycle)));

/*	savexw.writeStartElement("time");*/
	savexw.writeEmptyElement("time");
	savexw.writeAttribute(QXmlStreamAttribute("minute", QString("%1").arg(m_parameters.time()->minute())));
	savexw.writeAttribute(QXmlStreamAttribute("hour", QString("%1").arg(m_parameters.time()->hour())));
	savexw.writeAttribute(QXmlStreamAttribute("day", QString("%1").arg(m_parameters.time()->day())));
	savexw.writeAttribute(QXmlStreamAttribute("month", QString("%1").arg(m_parameters.time()->month())));
	savexw.writeAttribute(QXmlStreamAttribute("year", QString("%1").arg(m_parameters.time()->year())));
// 	savexw.writeEndElement();

	savexw.writeEmptyElement("wind");
	savexw.writeAttribute(QXmlStreamAttribute("v", QString("%1").arg(m_wind->v())));
	savexw.writeAttribute(QXmlStreamAttribute("dir", QString("%1").arg(m_wind->dir())));

	
	savexw.writeEndElement();

// 	savestream << gamedata->anbord << "\n";	// 10. Zeile + 1
// 	savestream << gamedata->currentMap.cityname << "\n";
// 	savestream << gamedata->currentMap.filename << "\n";



	savexw.writeStartElement("citylist");
	QHash<int, City*>::const_iterator savecity;
	
	const QHash<int, City*>::const_iterator lastcity = m_CityHash.end();
	
	for(savecity = m_CityHash.begin(); savecity != lastcity; ++savecity)
	{
		savexw.writeStartElement("city");
// 		savexw.writeAttribute(QXmlStreamAttribute("name", (*savecity)->name() ));
// 		savexw.writeAttribute(QXmlStreamAttribute("inhabitants", QString::number(savecity->inhabitants() )));
// 		savexw.writeAttributes(QXmlStreamAttributes((*savecity)->characteristics()));
// 		savexw.writeAttribute(QXmlStreamAttribute("m", savecity->storage().taler() ));
// 		savexw.writeAttribute(QXmlStreamAttribute("c", savecity->storage().capacity() ));
		/*
		QList <int> keylist = savecity->storage().keys();
		int i;
		foreach(i, keylist)
		{
			savexw.writeEmptyElement("storageitem");
			savexw.writeAttribute(QXmlStreamAttribute("id", QString("%1").arg(i)));
			savexw.writeAttribute(QXmlStreamAttribute("amount", QString("%1").arg(savecity->storage()[i])));
			savexw.writeAttribute(QXmlStreamAttribute("production", QString("%1").arg(savecity->production()[i])));
		}*/

		
		savexw.writeEndElement();
	}
	savexw.writeEndElement();


// 	ShipClass *saveship;
// 	Kontor 
// 	
// 	Object *objectit;
// 	QList<int> keylist = m_ObjectHash.keys();
// 	int keyit;
// 	foreach(keyit, keylist)
// 	{
// 	  
// 	}
/*
	Ship *saveship;

// 	QList <ShipClass> shiplist = gamedata->ret_ShipList();
// 	shiplist << *gamedata->active_ship;
	savexw.writeStartElement("shiplist");

 	foreach(saveship, m_ShipList)
	{
	  savexw.writeStartElement("ship");
	  savexw.writeAttribute(QXmlStreamAttribute("id", QString::number(saveship->id())));
	  savexw.writeAttribute(QXmlStreamAttribute("owner", QString::number(saveship->ownerID())));
	  savexw.writeAttribute(QXmlStreamAttribute("name", saveship->name()));
	  savexw.writeAttribute(QXmlStreamAttribute("state", QString::number(saveship->condition())));
	  savexw.writeAttribute(QXmlStreamAttribute("type", QString::number((int)(saveship->type()))));
	  savexw.writeAttribute(QXmlStreamAttribute("seamen", QString::number(saveship->seamen())));


	  
	  savexw.writeEmptyElement("nav");
	  savexw.writeAttributes(saveship->characteristics());

		QList <int> keylist = saveship->cargo().keys();
		int i;
		foreach(i, keylist)
		{
			savexw.writeEmptyElement("storageitem");
			savexw.writeAttribute(QXmlStreamAttribute("id", QString("%1").arg(i)));
			savexw.writeAttribute(QXmlStreamAttribute("amount", QString::number((*saveship)[i])));
		}
		savexw.writeEndElement();
	}
	savexw.writeEndElement();

	savexw.writeStartElement("kontorlist");

// 	shiplist.removeLast();
	Kontor *savekontor;
/*	QList<KontorClass> kontorlist = gamedata->ret_KontorList();
	foreach(*savekontor, kontorlist)
	{
		savestream << "<kontor>" << "\n";
		savestream << savekontor->ret_ID() << "\n";
		savestream << savekontor->ret_CityID() << "\n";
			for(int i = 0; i < const_warenanzahl; i++)
			{
				savestream << savekontor->storage.ware[i] << "\n";
				savestream << savekontor->production.ware[i];
			}
		savestream << savekontor->storage.taler << "\n";
		savestream << savekontor->storage.fuellung << "\n";
		savestream << savekontor->storage.kapazitaet << "\n";
		savestream << "</kontor>" << "\n";
	}


// 	savestream << gamedata->active_ship->id;
	savexw.writeEndElement();*/
	savexw.writeEndDocument();


							//muesste man mal mit der const-var belegen ...
// hf->endePause();
// aktiv=true;
}
// #endif




