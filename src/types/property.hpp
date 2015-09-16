/*
*
* The MIT License (MIT)
*
* Copyright (c) 2015 Walter Julius Hennecke
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/

#ifndef _GST_TYPES_PROPERTY_H
#define _GST_TYPES_PROPERTY_H

#include <functional>

namespace gst
{

  template <typename T>
  class property
  {
  public:
    property(const std::function<void(T& t, const T&v)>& s = nullptr, const std::function<T(const T& t)>& g = nullptr)
      : get(g)
      , set(s)
    {
    }

    std::function<void(T& tv, const T& v)> set;
    std::function<T(const T& tv)> get;

    const T& operator =(const T& Rhs)
    {
      if (set) set(_value, Rhs);
      else _value = Rhs;
      return _value;
    }

    operator T () const
    {
      if (get) return get(_value);
      else return _value;
    }

  private:
    T _value;
  };

}

#endif
