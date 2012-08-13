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

#ifndef _Array2D_H
#define _Array2D_H

#include <QtCore/QSize>

template <typename T>
class Array2D
{
public:
  Array2D(const QSize &a_arraysize) : m_arraysize(a_arraysize)
  {
    m_value = new T [(a_arraysize.height() * a_arraysize.width())];
  }
  /*
  template <class T>
  Array2D<T>::Array2D(int w, int h) : m_arraysize(w, h)
  
  
  template <class T>
  Array2D<T>::~Array2D()
  {
    delete [] m_value;
  }*/
  
  Array2D(int w, int h) : m_arraysize(w, h)
  {
    m_value = new T [w * h];
  }
  
  ~Array2D()
  {
    delete [] m_value;
  }
  
  //   T operator[][](int, int);
//   const T *operator[](int i) const;
  const T *operator[](int i) const
  {
    
//     return m_value + i * m_arraysize.height(); // = return &m_value[i * m_arraysize.height()];
    return &m_value[i * m_arraysize.height()];
  }

  T at(int a, int b) const
  {
    return value(a, b);
  }
  
  
  T value(int a, int b) const
  {
    if(a < m_arraysize.width() && b < m_arraysize.height())
      return m_value[a * m_arraysize.height() + b];
    else
      return m_value[0];
  }

  T &ref(int a, int b)
  {
    if(a < m_arraysize.width() && b < m_arraysize.height())
      return m_value[a * m_arraysize.height() + b];
    else
      return m_value[0];
  }
  
  T* pointer(int a, int b)
  {
    return &ref(a, b);
  }
  
private:
  T *m_value;
  QSize m_arraysize;

protected:

};

#endif
