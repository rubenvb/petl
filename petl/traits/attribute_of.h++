/**
 * The MIT License (MIT)
 *
 * Copyright © 2019 Ruben Van Boxem
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
 **/

/*
 * traits/attribute_of
 * Determine the attribute type of an expression.
 * Holds no_attribute if an expression does not parse into a value.
 */

#ifndef PETL_TRAITS_ATTRIBUTE_OF_H
#define PETL_TRAITS_ATTRIBUTE_OF_H

#include "petl/no_attribute.h++"

namespace petl
{
  template<typename... T>
  struct attribute_of;

  template<typename T>
  struct attribute_of<T>
  {
    using type = typename T::attribute_type;
  };

  template<>
  struct attribute_of<>
  {
    using type = no_attribute;
  };

  template<typename T>
  using attribute_of_t = typename attribute_of<T>::type;
}

#endif
