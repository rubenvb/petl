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
 * utility/flatten
 * Flattens a tuple (of tuples) to at most one tuple containing all recursive sub-elements.
 */

#ifndef PETL_UTILITY_FLATTEN_H
#define PETL_UTILITY_FLATTEN_H

#include "petl/traits/is_tuple.h++"
#include "petl/utility/tuple_rank.h++"

#include <array>

namespace petl::utility
{
  // TODO: get rid of tag type
  template<typename T>
  struct Type
  {// tag type
    using type = T;
  };

  // TODO: get rid of while loop if result is decent
  template<std::size_t RankPosition, typename... Types>
  constexpr auto extract_index()
  {
    static_assert(sizeof...(Types) >= 1, "do not extract from empty tuples");

    constexpr auto ranks = std::array{tuple_rank_v<Types>...};

    std::size_t index = 0;
    std::size_t nested_rankpos = RankPosition;

    while(nested_rankpos >= ranks[index])
    {
      nested_rankpos -= ranks[index++];
    }

    return std::pair{index, nested_rankpos};
  }

  ////////////////////////////////////////////////////////////////////////////////

  template<std::size_t rankpos, typename T>
  constexpr auto tuple_element_at_rankpos_tag(Type<T>)
  {
    static_assert(rankpos == 0);
    return Type<T>{};
  }

  template<std::size_t rankpos, typename... Ts>
  constexpr auto tuple_element_at_rankpos_tag(Type<std::tuple<Ts...>>)
  {
    // constexpr auto [index, nested_rankpos] = extract_index(rankpos, tuple_tag);
    constexpr std::pair pair = extract_index<rankpos, Ts...>();
    constexpr std::size_t index = pair.first;
    constexpr std::size_t nested_rankpos = pair.second;

    using NestedType = std::tuple_element_t<index, std::tuple<Ts...>>;

    return tuple_element_at_rankpos_tag<nested_rankpos>(Type<NestedType>{});
  }

  template<std::size_t rankpos, typename Tuple>
  using tuple_element_at_rankpos_t = typename decltype(tuple_element_at_rankpos_tag<rankpos>(Type<Tuple>{}))::type;

  template<std::size_t rankpos, typename Element, typename T>
  constexpr decltype(auto) get_at_rankpos(Element&& element,
                                          Type<T>) /* element_tag */
  {
    static_assert(rankpos == 0);
    return std::forward<Element>(element);
  }

  template<std::size_t rankpos, typename... Ts, typename Tuple>
  constexpr decltype(auto) get_at_rankpos(Tuple&& tuple,
                                          Type<std::tuple<Ts...>>)
  {
    // constexpr auto [index, nested_rankpos] = extract_index(rankpos, tuple_tag);
    constexpr std::pair pair = extract_index<rankpos, Ts...>();
    constexpr std::size_t index = pair.first;
    constexpr std::size_t nested_rankpos = pair.second;

    using NestedType = std::tuple_element_t<index, std::tuple<Ts...>>;

    return get_at_rankpos<nested_rankpos>(std::get<index>(std::forward<Tuple>(tuple)),
                                          Type<NestedType>{});
  }

  template<typename... Ts, typename Tuple, std::size_t... rank_positions>
  constexpr auto flatten_impl(Tuple&& tuple,
                              std::index_sequence<rank_positions...>,
                              Type<std::tuple<Ts...>> tuple_tag)
  {
    return std::tuple<tuple_element_at_rankpos_t<rank_positions, std::tuple<Ts...>>...>
    {
      get_at_rankpos<rank_positions>(std::forward<Tuple>(tuple), tuple_tag)...
    };
  }

  template<typename T,
           typename = std::enable_if_t<!traits::is_tuple_v<std::remove_cv_t<std::remove_reference_t<T>>>, void>>
  constexpr T&& flatten(T&& non_tuple)
  {
    return std::forward<T>(non_tuple);
  }

  template<typename TupleType,
           typename = std::enable_if_t<traits::is_tuple_v<std::remove_cv_t<std::remove_reference_t<TupleType>>>, void>>
  constexpr auto flatten(TupleType&& tuple)
  {
    using UnqualifiedTupleType = std::remove_cv_t<std::remove_reference_t<TupleType>>;

    using TupleTag = Type<UnqualifiedTupleType>;
    constexpr auto rank = tuple_rank_v<UnqualifiedTupleType>;

    return flatten_impl(std::move(tuple), std::make_index_sequence<rank>{}, TupleTag{});
  }

  // TODO: merge these single-element tuple cases into one
  template<typename T>
  constexpr auto flatten(std::tuple<T>& tuple)
  {
    return flatten(std::get<0>(tuple));
  }

  template<typename T>
  constexpr auto flatten(std::tuple<T>&& tuple)
  {
    return flatten(std::get<0>(tuple));
  }

  template<typename T>
  constexpr auto flatten(const std::tuple<T>& tuple)
  {
    return flatten(std::get<0>(tuple));
  }
}

#endif
