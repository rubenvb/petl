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

#include "test.h++"

#include <petl/flatten.h++>

namespace
{
  using petl::expression::sequence;

  constexpr auto single_expression = 42;
  constexpr auto single_expression_sequence = sequence<int>{single_expression};

  constexpr auto simple_sequence = sequence<int, double>{42, 42.};

  constexpr auto single_nested_single_expression_sequence = sequence<sequence<int>>{single_expression_sequence};
  constexpr auto single_nested_simple_sequence = sequence<sequence<int, double>>{simple_sequence};
  constexpr auto simple_nested_simple_sequence = sequence<sequence<int, double>, sequence<int, double>>{simple_sequence, simple_sequence};

}

constexpr auto bare = 42;
constexpr auto& bare_ref = bare;

constexpr auto single = std::make_tuple(bare);
constexpr auto nested_simple = std::make_tuple(single);

constexpr auto multiple = std::make_tuple(bare, bare);
constexpr auto nested_multiple = std::tuple{multiple};

constexpr auto multiply_nested = std::make_tuple(multiple, multiple);

constexpr auto mixed = std::make_tuple(single, multiple, nested_multiple, multiply_nested);

static_assert(petl::flatten(bare) == bare);
static_assert(petl::flatten(bare_ref) == bare_ref);

static_assert(petl::flatten(single) == bare);
static_assert(petl::flatten(nested_simple) == bare);

static_assert(petl::flatten(multiple) == multiple);
static_assert(petl::flatten(nested_multiple) == multiple);

static_assert(petl::flatten(multiply_nested) == std::make_tuple(bare, bare, bare, bare));

static_assert(petl::flatten(mixed) == std::make_tuple(bare,
                                                      bare, bare,
                                                      bare, bare,
                                                      bare, bare, bare, bare));

//static_assert(petl::flatten(single_expression) == single_expression);

//static_assert(petl::flatten(simple_sequence) == simple_sequence);

//static_assert(petl::flatten(single_nested_single_expression_sequence) == single_expression);
//static_assert(petl::flatten(single_nested_simple_sequence) == simple_sequence);
//static_assert(petl::flatten(single_))

int main(){}
