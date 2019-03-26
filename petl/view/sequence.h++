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

#ifndef PETL_SEQUENCE_H
#define PETL_SEQUENCE_H

#include "petl/traits/class_type.h++"
#include "petl/traits/first_type.h++"
#include "petl/traits/pointee_type.h++"

#include <any>
#include <tuple>

namespace petl
{
  template<auto... PointersToMembers>
  struct sequence;

  template<std::size_t Index, auto... PointersToMembers>
  decltype(auto) get(sequence<PointersToMembers...>& sequence);

  template<auto... PointersToMembers>
  struct sequence
  {
    static_assert((std::is_member_pointer_v<decltype(PointersToMembers)> && ...));

    using sequenced_type = class_type_t<first_type_t<decltype(PointersToMembers)...>>;

    static_assert((std::is_same_v<sequenced_type, class_type_t<decltype(PointersToMembers)>> && ...));

    sequence(sequenced_type& object)
      : object{object}
    {}

    sequenced_type& object;
    constexpr static std::tuple members{PointersToMembers...};
  };

  template<std::size_t Index, auto... PointersToMembers>
  decltype(auto) get(sequence<PointersToMembers...>& sequence)
  {
    auto pointer_to_member = std::get<Index>(sequence.members);
    return sequence.object.*pointer_to_member;
  }
}

#endif
