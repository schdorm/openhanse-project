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

#include "omath.h"
#include <QtCore/QByteArray>
#include <QtCore/QString>

#include <math.h>
#include <stdlib.h>

bool isPositive(int number)
{
  if(number > 0)
  {
    return true;
  }
  else
    return false;
}

int hexToDec(const QByteArray &hex)
{
  int result = 0; int position = 0;
  char atPos;
  for(int i=hex.size(); i; i--)
  {
    atPos = hex.at(i-1);
    switch(atPos)
    {
      case '0':
	break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':	
      {
	result+=pow(16,position)* atoi(&atPos);
	break;
      }
      case 'A':
      case 'a':
      {
	result += pow(16,position)* 10;
	break;
      }
      case 'B':
      case 'b':
      {
	result += pow(16,position)* 11;
	break;
      }
      case 'C':
      case 'c':
      {
	result += pow(16,position)* 12;
	break;
      }
      case 'D':
      case 'd':
      {
	result += pow(16,position)* 13;
	break;
      }
      case 'E':
      case 'e':
      {
	result += pow(16,position)* 14;
	break;
      }
      case 'F':
      case 'f':
      {
	result += pow(16,position)* 15;
	break;
      }
      default:
	return 0;
    }
    position++;
  }
  return result;
}

QString toHex(int number)
{
  int div;
  QString result;
  while(number >= 1)
  {
    div = number %16;
    switch(div)
    {
      case 10:
      {
	result.prepend('A');
	break;
      }
      case 11:
      {
	result.prepend('B');
	break;
      }
      case 12:
      {
	result.prepend('C');
	break;
      }
      case 13:
      {
	result.prepend('D');
	break;
      }
      case 14:
      {
	result.prepend('E');
	break;
      }
      case 15:
      {
	result.prepend('F');
	break;
      }
      default:
      {
	result.prepend(QString::number(div));
      }
    }
    number /= 16;
  }
  return result.prepend("0");
}


