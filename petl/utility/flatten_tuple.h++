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
 * utility/flatten_tuple
 * Flattens a tuple (of tuples) to at most one tuple containing all recursive sub-elements.
 */

#ifndef PETL_FLATTEN_TUPLE_H
#define PETL_FLATTEN_TUPLE_H

#include "petl/traits/is_tuple.h++"

#include "petl/utility/as_tuple.h++"

namespace petl::utility
{
  template<typename T>
  constexpr decltype(auto) flatten_tuple(T t)
  {
    return t;
  }

  template<typename T>
  constexpr decltype(auto) flatten_tuple(std::tuple<T> t)
  {
    return flatten_tuple(std::get<0>(t));
  }

  template<typename ...Ts,
           std::enable_if_t<std::negation_v<std::disjunction<traits::is_tuple<Ts>...>>, bool> = false>
  constexpr decltype(auto) flatten_tuple(std::tuple<Ts...> t)
  {
    return t;
  }

  template<typename ...Ts,
           std::enable_if_t<std::disjunction_v<traits::is_tuple<Ts>...>, bool> = false>
  constexpr decltype(auto) flatten_tuple(std::tuple<Ts...> t)
  {
    return std::apply([](auto&&...ts) { return flatten_tuple(std::tuple_cat(as_tuple(flatten_tuple(std::forward<decltype(ts)>(ts)))...)); }, t);
  }
}

#endif
