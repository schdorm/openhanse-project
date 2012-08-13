/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
 *   schdorm@googlemail.com                                                *
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

#include "libs/array2d.h"

/*template <class T>
Array2D<T>::Array2D(const QSize &a_arraysize) : m_arraysize(a_arraysize)
{
  m_value = new T [a_arraysize.height() * a_arraysize.width()];
}

template <class T>
Array2D<T>::Array2D(int w, int h) : m_arraysize(w, h)
{
  m_value = new T [w * h];
}*/

/*template <class T>
Array2D<T>::~Array2D()
{
  delete [] m_value;
}*/

/*template <class T>
T &Array2D<T>::operator[][](int a, int b)
{
  if(a < m_arraysize.width() && b < m_arraysize.height())
    return m_value[a * m_arraysize.height() + b);
  
}*/
/*
template <class T>
T * Array2D<T>::operator[](int i)
{
  return m_value + i * m_arraysize.height(); // = return &m_value[i * m_arraysize.height()];
}

template <class T>
T Array2D<T>::at(int a, int b) const
{
  return value(a, b);
}

template <class T>
T Array2D<T>::value(int a, int b) const
{
  if(a < m_arraysize.width() && b < m_arraysize.height())
    return m_value[a * m_arraysize.height() + b];
  else
    return T();
}


template <class T>
T &Array2D<T>::ref(int a, int b)
{
  if(a < m_arraysize.width() && b < m_arraysize.height())
    return m_value[a * m_arraysize.height() + b];
  else
    return m_value[0];
}
*/
