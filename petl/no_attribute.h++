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
 * no_attribute
 * Type used to signify an expression has no attribute.
 */

#ifndef PETL_NO_ATTRIBUTE_H
#define PETL_NO_ATTRIBUTE_H

#include <tuple>

namespace petl
{
  struct no_attribute {};

  template<typename... T>
  struct filter_no_attribute;

  template<typename T>
  struct filter_no_attribute<T>
  {
    using type = std::tuple<T>;
  };
  template<>
  struct filter_no_attribute<>
  {
    using type = std::tuple<>;
  };

  template<>
  struct filter_no_attribute<no_attribute> : filter_no_attribute<>{};

  template<typename... T>
  struct tuple_filter_no_attribute;

  template<typename... T>
  struct tuple_filter_no_attribute
  {
    using type = decltype(std::tuple_cat(std::declval<typename filter_no_attribute<T>::type>()...));
  };

  template<>
  struct tuple_filter_no_attribute<>
  {
    using type = std::tuple<>;
  };
  template<>
  struct tuple_filter_no_attribute<no_attribute> : tuple_filter_no_attribute<> {};

  template<typename... T>
  using tuple_filter_no_attribute_t = typename tuple_filter_no_attribute<T...>::type;
}

#endif
