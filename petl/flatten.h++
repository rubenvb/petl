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

#ifndef PETL_FLATTEN_H
#define PETL_FLATTEN_H

#include "petl/expression/sequence.h++"

#include "petl/traits/is_tuple.h++"

#include "petl/utility/as.h++"

namespace petl
{
  template<typename T>
  constexpr decltype(auto) flatten(T t)
  {
      return t;
  }

  template<typename T>
  constexpr decltype(auto) flatten(std::tuple<T> t)
  {
      return flatten(std::forward<T>(std::get<0>(t)));
  }

  template<typename ...Ts,
           std::enable_if_t<!(is_tuple<Ts>::value || ...), bool> = false>
  constexpr decltype(auto) flatten(std::tuple<Ts...> t)
  {
      return t;
  }

  template<typename ...Ts,
           std::enable_if_t<(is_tuple<Ts>::value || ...), bool> = false>
  constexpr decltype(auto) flatten(std::tuple<Ts...> t)
  {
      return std::apply([](auto&&...ts){ return flatten(std::tuple_cat(as_tuple(flatten(std::forward<decltype(ts)>(ts)))...)); }, t);
  }
}

#endif
