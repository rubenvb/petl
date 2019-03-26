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
 * utility/tuple_rank
 * Gets the total number of recursive elements in a tuple.
 */

#ifndef PETL_TUPLE_RANK_H
#define PETL_TUPLE_RANK_H

namespace petl::utility
{
  template<typename T>
  struct tuple_rank;

  template<typename T>
  constexpr auto tuple_rank_v = tuple_rank<T>::value;

  template<typename T>
  struct tuple_rank : std::integral_constant<std::size_t, 1> {};

  template<typename... Ts>
  struct tuple_rank<std::tuple<Ts...>>
      : std::integral_constant<std::size_t, (tuple_rank_v<Ts> + ...)> {};

  template<typename... Ts>
  struct tuple_rank<const std::tuple<Ts...>> : tuple_rank<std::tuple<Ts...>> {};
  template<typename... Ts>
  struct tuple_rank<volatile std::tuple<Ts...>> : tuple_rank<std::tuple<Ts...>> {};
  template<typename... Ts>
  struct tuple_rank<const volatile std::tuple<Ts...>> : tuple_rank<std::tuple<Ts...>> {};
}

#endif
