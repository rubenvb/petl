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
 * expression/sequence
 *
 */

#ifndef PETL_EXPRESSION_SEQUENCE_H
#define PETL_EXPRESSION_SEQUENCE_H

#include "petl/traits/attribute_of.h++"
#include "petl/traits/first_type.h++"

#include "petl/utility/as_tuple.h++"

#include <cstddef>
#include <tuple>

namespace petl::expression
{
  template<typename... Expressions>
  struct sequence
  {
    using attribute_type = tuple_filter_no_attribute_t<attribute_of_t<Expressions>...>;
    using expressions_type = std::tuple<Expressions...>;

    static constexpr auto size = sizeof...(Expressions);

    static_assert(size > 0);

    template<typename... InputExpressions>
    sequence(InputExpressions&&... input_expressions)
      : expressions{std::forward_as_tuple(input_expressions...)}
    {}

    constexpr static auto from_expression_tuple(std::tuple<Expressions...> expressions)
    {
      return make_sequence(expressions,
                           std::make_index_sequence<size>());
    }

    const expressions_type expressions;

  private:
    template<typename Tuple,
             std::size_t... Indices>
    constexpr static auto make_sequence(Tuple&& t,
                                        std::index_sequence<Indices...>)
    {
      (void)t;
      return sequence<std::tuple_element_t<Indices, std::decay_t<Tuple>>...>{std::get<Indices>(t) ...};
    }
  };

  template<typename... Expressions>
  sequence(Expressions&&...) -> sequence<Expressions...>;

  template<typename... LeftExpressions, typename... RightExpressions>
  constexpr bool operator==(const sequence<LeftExpressions...>& lhs,
                            const sequence<RightExpressions...>& rhs)
  {
    return lhs.expressions == rhs.expressions;
  }
  template<typename... LeftExpressions, typename... RightExpressions>
  constexpr bool operator!=(const sequence<LeftExpressions...>& lhs,
                            const sequence<RightExpressions...>& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename LeftExpression, typename RightExpression>
  auto operator>>(LeftExpression&& lhs,
                  RightExpression&& rhs)
  {
    return sequence<std::decay_t<LeftExpression>, std::decay_t<RightExpression>>
    {
      std::forward<LeftExpression>(lhs),
      std::forward<RightExpression>(rhs)
    };
  }
  template<typename LeftExpression, typename... RightExpressions>
  auto operator>>(LeftExpression&& lhs,
                  sequence<RightExpressions...> rhs)
  {
    using sequence_type = sequence<std::decay_t<LeftExpression>, RightExpressions...>;
    return sequence_type::from_expression_tuple(std::tuple_cat(as_tuple(std::forward<LeftExpression>(lhs)),
                                                               rhs.expressions));
  }
  template<typename... LeftExpressions, typename RightExpression>
  auto operator>>(sequence<LeftExpressions...> lhs,
                  RightExpression&& rhs)
  {
    using sequence_type = sequence<LeftExpressions..., std::decay_t<RightExpression>>;

    return sequence_type::from_expression_tuple(std::tuple_cat(as_tuple(std::move(lhs.expressions)),
                                                               as_tuple(std::forward<RightExpression>(rhs))));
  }

  template<typename Expression>
  constexpr std::size_t sequence_length = 1;
  template<typename... Expressions>
  constexpr std::size_t sequence_length<sequence<Expressions...>> = sizeof...(Expressions);

  template<typename Expression>
  struct is_sequence : std::false_type {};
  template<typename... Expressions>
  struct is_sequence<sequence<Expressions...>> : std::true_type {};

  template<typename Expression>
  constexpr bool is_sequence_v = is_sequence<Expression>::value;
}

#endif

//#include "sequence/flatten_sequence.h++"
//#include "sequence/sequence_operator.h++"
