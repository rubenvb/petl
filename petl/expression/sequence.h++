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

#ifndef PETL_EXPRESSION_SEQUENCE
#define PETL_EXPRESSION_SEQUENCE

#include <cstddef>
#include <tuple>

namespace petl
{
  namespace expression
  {
    template<typename... Expressions>
    struct sequence
    {
      template<typename... InputExpressions>
      constexpr sequence(InputExpressions&&... expressions)
        : expressions{std::forward<InputExpressions>(expressions)...}
      {}

      static constexpr auto size = sizeof...(Expressions);

      std::tuple<Expressions...> expressions;
    };
    template<typename... Expressions>
    sequence(Expressions&&...) -> sequence<Expressions...>;

    template<typename... LeftExpressions, typename... RightExpressions>
    constexpr bool operator==(const sequence<LeftExpressions...>& left,
                              const sequence<RightExpressions...>& right)
    {
      return left.expressions == right.expressions;
    }

    template<typename Expression>
    constexpr std::size_t sequence_length = 1;
    template<typename... Expressions>
    constexpr std::size_t sequence_length<sequence<Expressions...>> = sizeof...(Expressions);
  }
}

#endif
