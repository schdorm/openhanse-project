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

#include "data/abstractmap.h"
#include "data/abstractmapobject.h"
#include "data/abstractcity.h"

#include "libs/oqstring.h"

// #define DEBUG_MAP

// int AbstractMap::mapcounter = 0;


#ifdef DEBUG_MAP
#include <QtDebug>
#endif

#include <QtCore/QVariant>

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include <QtCore/QXmlStreamReader>
#include <QtXml/QXmlStreamWriter>




/*AbstractMap::AbstractMap(const AbstractMap &other) : m_coordinates(other.coordinates()), m_size(other.size()), m_background (other.background()), 
	     m_mapnorth (other.mapnorth()),
	     m_mapeast (other.mapeast()),
	     m_mapsouth (other.mapsouth()),
	     m_mapwest(other.mapwest()), m_type (other.type())
{
  mapcounter ++;
  qWarning() << "Count of map instances:" << mapcounter;
}*/

AbstractMap::AbstractMap() : m_filename (QString()),
	     m_size (QSize(1023,1023)),
	     m_background (QString("0")),
	     m_mapnorth (QString("0")),
	     m_mapeast (QString("0")),
	     m_mapsouth (QString("0")),
	     m_mapwest (QString("0")),
	     m_type (Sea),
	     m_city (0)
	     {
	       m_type = Sea;
	       
	       
/// mapcounter ++;
///   qWarning() << "Count of map instances:" << mapcounter;
// m_mapdirectory = SETTINGS->mapdirectory();
// 	if(mapdirectory.isEmpty())			// static QString in AbstractMap-Class
// 	{
// 		QDir dir= QDir().current();
// 		if(dir.cd("maps"))
// 		{
// 			mapdirectory = dir.absolutePath().append("/");
// 			qWarning()  << "Working Direktory:" << mapdirectory;
// 			
// 		}
// 		else
// 		{
// 			qWarning() << "AbstractMapdir does not exist. Exiting.";
// 			mapdirectory = QString();
// 		}
// 	}
}

/*AbstractMap::AbstractMap(const AbstractMap *other) :
  m_filename (other->filename()),
  m_coordinates (other->coordinates()),
  m_size (other->size()),
  m_background (other->background()),
  m_mapnorth (other->mapnorth()),
  m_mapeast (other->mapeast()),
  m_mapsouth (other->mapsouth()),
  m_mapwest (other->mapwest()),
  m_type (other->type()),
  m_city (0),
  m_Objects (other->m_Objects)

{
    if(!other->city() == 0 )
      if(isCity() && other->isCity())
      {
	#ifdef DEBUG_MAP
	qWarning() << "before copiing city";
	#endif
	m_city = new AbstractCity(*other->city());
	
	m_city->setID(m_id);
	
	#ifdef DEBUG_MAP
	qWarning() << "after copiiing city";
	#endif
      }
      
  ///mapcounter ++;
  ///qWarning() << "Count of map instances:" << mapcounter;
}*/

/*AbstractMap::~AbstractMap()
{
  ///static int diff;
  ///diff++;
  ///qWarning() << "Count of map instances:" << mapcounter << "Active:" << mapcounter - diff;
  
// #ifdef _DEBUG_DESTRUCTORS
// qWarning() << "Destructing AbstractMap";
// #endif
//  AbstractMapObject *mapobjectit = 0;	//AbstractMap-Object-Iterator
//  foreach(mapobjectit, m_ObjectList)
//  {
//     delete mapobjectit;
//  }
// #ifdef _DEBUG_DESTRUCTORS
// #endif
// qWarning() << "deleting city";
// if(!(m_city == NULL))
//    delete m_city;
qWarning() << "End of Destructing AbstractMap";

}*/

void AbstractMap::setCity(const AbstractCity &otherCity)
{
  //   delet e m_city;
  #ifdef DEBUG_MAP
  qWarning() << "SetCity";
  #endif
  
//   m_city = otherCity;
  *(cityinstance()) = otherCity;
  
  #ifdef DEBUG_MAP
  qWarning() << "City setted";
  #endif
}


AbstractCity *AbstractMap::cityinstance()
{
  #ifdef DEBUG_MAP
  qWarning() << "Cityinstance()";
  #endif
  if(m_city == NULL)
  {
    #ifdef DEBUG_MAP
    qWarning() << "New instance";
    #endif
    m_city = new AbstractCity();
  }
  if(!isCity())
  {
    m_type ^= Citymap;
  }
  #ifdef DEBUG_MAP
  qWarning() << "Return city";
  #endif
  
  return m_city;
}


// const City *city()	const;
// {
//   return m_city;
// }



bool AbstractMap::isCity() const
{
  return ((m_type == (Coast ^ Citymap)) || (m_type == (Land ^ Citymap)));
}



/*void AbstractMap::loadStartAbstractMap(const QString &mapfilename)
{
static bool started;
if(!started)
{
started = load(mapfilename);
m_coordinates = QPoint(400,400);
}
else if(mapfilename == "false")
{
started = false;
}

}*/



// #include <QtDebug>

#define LOAD_save_MAPOBJECTS


bool AbstractMap::load(const QString &a_filename)
{
  #ifdef DEBUG_MAP
  qWarning() << "bool AbstractMap::load(const QString &a_filename)" << " (Karteladen): " << a_filename;
  #endif
  QString mapdirectory = QFileInfo(a_filename).absoluteDir().absolutePath();
  
  QFile file(a_filename);		//AbstractMap-XML-Lesen
  if(file.exists())
  {
    m_filename = a_filename;
    #ifdef DEBUG_MAP
    qWarning() << "AbstractMapfile is existing";
    #endif
    
    if(file.open(QIODevice::ReadOnly))
    {
      QXmlStreamReader reader(&file);
      while (!reader.atEnd()) 
      {
	switch(reader.readNext())
	{
	  case QXmlStreamReader::StartElement:
	  {
	    QStringRef elementname = reader.name();
	    #ifdef DEBUG_MAP
	    qWarning() << "\nStart:\t" << elementname.toString();
	    #endif
	    
#ifndef LOAD_save_MAPOBJECTS
	    if(elementname == "object")
	    {
	      QXmlStreamAttributes objectattributes = reader.attributes();
	      
	      #ifdef DEBUG_MAP
	      for(QXmlStreamAttributes::const_iterator it = objectattributes.begin(); it != objectattributes.end(); ++it)
		qWarning() << "add Object:" << it->name() << it->value() ;
	      #endif
	      
	      m_ObjectList << AbstractMapObject(objectattributes.value("role").toString().toInt(),(objectattributes.value("file").toString()), toPoint(objectattributes.value("position").toString()), (objectattributes.value("tooltip").toString()), (objectattributes.value("name").toString()), objectattributes.value("zvalue").toString().toDouble());
	      
	      break;
	    }
	    
#endif

///******************************************************************************************************///

#ifdef LOAD_save_MAPOBJECTS

	    if(elementname == "objects")
	    {
	      bool objects = true;
	      QStringRef it_name;
	      
	      QStringRef f_file, f_position, f_name, f_tooltip, f_img;
	      int f_role(-1);
	      double f_zvalue(0);
	      
	      while(objects)
	      {
		switch(reader.readNext())
		{
		  case QXmlStreamReader::StartElement:
		  {
		    if(reader.name() == "object")
		    {
		      QXmlStreamAttributes objectattributes = reader.attributes();
		      for(QXmlStreamAttributes::const_iterator it = objectattributes.begin(); it != objectattributes.end(); ++it)
		      {
			it_name = it->name();
			#ifdef DEBUG_MAP
			qWarning() << it_name;
			#endif
			if(it_name == "role")
			{
			  f_role = it->value().toString().toInt();
			}
			else if(it_name == "file")
			{
			  f_file = it->value();
			}
			else if(it_name == "position")
			{
			  f_position = it->value();
			}
			else if(it_name == "zvalue")
			{
			  f_zvalue = it->value().toString().toDouble();
			}
			else if (it_name == "name")
			{
			  f_name = it->value();
			}
			else if(it_name == "tooltip")
			{
			  f_tooltip = it->value();
			}
			else if(it_name == "image")
			{
			  f_img = it->value();
			}
		      }
		      
		      #ifdef DEBUG_MAP
		      qWarning() << "File/Pos/Name/Tooltip" << f_file << f_position << f_name << f_tooltip;
		      #endif
		      if(!f_file.isEmpty())
		      {
			if(!f_img.isEmpty() && QFileInfo(f_img.toString()).exists())
			{
			  AbstractMapObject newMO(f_role, f_img.toString(), StringToPoint(f_position.toString()), f_name.toString() , f_tooltip.toString(), f_zvalue);
			  m_Objects.insert(newMO.id(), newMO);
			}
			else
			{
			  AbstractMapObject newMO(f_role, f_file.toString(), StringToPoint(f_position.toString()), f_name.toString() , f_tooltip.toString(), f_zvalue);
			  m_Objects.insert(newMO.id(), newMO);
			}
			
		      }
		      
		      f_file = f_img = QStringRef();
		      
		      f_file = f_position = f_name = f_tooltip = QStringRef();
		      f_role = -1;
		      f_zvalue = 0;
		      
		    }
		    break;
		  }
		  case QXmlStreamReader::EndElement:
		  {
		    if(reader.name() == "objects")
		    {
		      objects = false;
		    }
		    break;
		  }
		  default:
		    break;
		}
	      }
	      break;
	    }
	    #endif
	    
	    else if(elementname == "city")
	    {

	      *(cityinstance()) = AbstractCity(m_id, reader.attributes().value("name").toString()/*, reader.attributes().value("id").toString().toInt()*/);
	      /// City-ID
	      // 				  cityname = reader.attributes().value("name").toString();
	      // 				  id = reader.attributes().value("id").toString().toInt();
	      // 				  m_city.setName(cityname);
	      // 				  m_city.setID(id);
	      // 				  status = e_map_cityname;
	      break;
	    }/*
	    else if(reader.name().toString() == "production" && isCity())
	    {
// 				  QString lowp = reader.attributes().value("low").toString();
// 				  QString nmlp = reader.attributes().value("normal").toString();
// 				  QString highp = reader.attributes().value("high").toString();
	      m_city.setProduction(Goods::LowProduction, reader.attributes().value("low").toString());
	      m_city.setProduction(Goods::NormalProduction, reader.attributes().value("normal").toString());
	      m_city.setProduction(Goods::HighProduction, reader.attributes().value("high").toString());
	      break;
	    }*/
	    else if(reader.name() == "production_goods" && isCity())
	    {
	      m_city->production().setXmlAttributes(reader.attributes());
	    }
	    else if(reader.name().toString() == "map")
	    {
	       #ifdef DEBUG_MAP
	      qWarning() << reader.attributes().value("height").string()->toInt() << reader.attributes().value("height").toString().toInt();
	      #endif
// 	      m_size.setHeight(reader.attributes().value("height").string()->toInt());
// 	      m_size.setWidth(reader.attributes().value("width").string()->toInt());
	      m_size.setHeight(reader.attributes().value("height").toString().toInt());
	      m_size.setWidth(reader.attributes().value("width").toString().toInt());

	      m_type = reader.attributes().value("type").toString().toInt();
	      m_background = reader.attributes().value("background").toString();
	      break;
	    }
	    else if(reader.name().toString() == "adjoining_maps")
	    {
	      m_mapnorth= (reader.attributes().value("north").toString());
	      m_mapeast	= (reader.attributes().value("east").toString());
	      m_mapsouth= (reader.attributes().value("south").toString());
	      m_mapwest	= (reader.attributes().value("west").toString());
	      break;
	    }
	    break;
	  }
	  /// END : CASE StartElement
	  #ifdef DEBUG_MAP
	  case QXmlStreamReader::Invalid:
	  {
	    qWarning() << "Error:" << reader.errorString() <<"\nEnde Error" ;
	    break;
	  }

	  case QXmlStreamReader::Characters:
	  {
	    qWarning() << "Characters:" << reader.text().toString();
	    break;
	  }
	  case QXmlStreamReader::EndElement:
	  {
	    qWarning() << "Ende :"<< reader.name().toString();
/*				if(reader.name().toString() == "object" && object_role != - 1 && !object_file.isEmpty())
	//jetzt zeichnen: habe alle Eigenschaften des Objektes erhalten?
				{
					qWarning() << object_file << object_role;
					
					AbstractMapObject currentMO = AbstractMapObject(object_role, object_file, object_tooltip, QPoint(object_posx, object_posy), object_zvalue);
					
					m_ObjectList << currentMO;
					
					object_role = -1;
					object_tooltip = QString();
					object_file = QString();
					object_posx = 0;
					object_posy = 0;
					object_zvalue = 0;
					 {
					   {
					     {
					       {
						 {
						   {
						     {
						       {
						       }
						     }
						   }
						 }
						 
					       }
					     }
					   }
					 }
					 
				}
				status = e_null;*/
	    break;
	  }
	#endif
	default:
	  break;
	}
	
	if (reader.hasError())
	{
	  #ifdef DEBUG_MAP
	  qWarning() << reader.errorString();
	  #endif
	  #ifndef DEBUG_MAP
	  qWarning(reader.errorString().toUtf8().data());
	  #endif
	  
	}
	
      }
      #ifdef DEBUG_MAP
      qWarning() << "Returning true: AbstractMap sucessfully read!";
      #endif
      return true;
    }
  }
  return false;
  
}

void AbstractMap::addObject(const AbstractMapObject *a_newAMO)
{
  if(a_newAMO != 0)
  {
    m_Objects[a_newAMO->id()] = (*a_newAMO);
  }
}


void AbstractMap::removeObject(int a_id)
{
  m_Objects.remove(a_id);
}



void AbstractMap::setName(const QString &a_name)
{
  m_name = a_name;
}


void AbstractMap::setCoordinates	(const QPoint &nc)
{
  m_coordinates = nc;
}

void AbstractMap::setSize		(const QSize &ns)
{
  m_size = ns;
}

void AbstractMap::setBackground	(const QString &nbg)
{
  m_background = nbg;
}

void AbstractMap::setMapnorth	(const QString &nmn)
{
  m_mapnorth = nmn;
}

void AbstractMap::setMapsouth	(const QString &nms)
{
  m_mapsouth = nms;
}

void AbstractMap::setMapwest		(const QString &nmw)
{
  m_mapwest = nmw;
}

void AbstractMap::setMapeast		(const QString &nme)
{
  m_mapeast = nme;
}

void AbstractMap::setType(int a_type)
{
  m_type = a_type;
}



AbstractMap &operator<=(AbstractMap &m1, const AbstractMap &m2)
{
  #ifdef DEBUG_MAP
  qWarning() << "AbstractMap &operator<=(AbstractMap &m1, const AbstractMap &m2)";
  #endif
  
  m1.setBackground(m2.background());
  m1.setCoordinates(m2.coordinates());
  m1.setMapeast(m2.mapeast());
  m1.setMapnorth(m2.mapnorth());
  m1.setMapsouth(m2.mapsouth());
  m1.setMapwest(m2.mapwest());
  m1.setSize(m2.size());
  
  #ifdef DEBUG_MAP
  qWarning() << "  int m2type = m2.type();";
  #endif
  
  int m2type = m2.type();
  m1.setType(m2type);
  if(m2.isCity() && m2.city() != 0)
  {
    
    #ifdef DEBUG_MAP
    qWarning() << "    m1.setCity(m2.city());" << m2.city()->name();
    #endif
    
    //     if(m2.city() != 0)
    m1.setCity(*m2.city());
  }
  
  #ifdef DEBUG_MAP
  qWarning() << "  return m1;";
  #endif
  
  return m1;
}


