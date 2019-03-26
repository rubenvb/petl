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

#ifndef TUPLE_TEST_TYPES_H
#define TUPLE_TEST_TYPES_H

#include <tuple>

constexpr auto bare = 42;
constexpr auto& bare_ref = bare;

constexpr auto single = std::make_tuple(bare);
constexpr auto nested_simple = std::make_tuple(single);

constexpr auto multiple = std::make_tuple(bare, bare);
constexpr auto nested_multiple = std::make_tuple(multiple);

constexpr auto multiply_nested = std::make_tuple(multiple, multiple);

constexpr auto mixed = std::make_tuple(single, multiple, nested_multiple, multiply_nested);

constexpr auto single_ref = std::make_tuple<std::add_lvalue_reference_t<decltype(bare)>>(bare);


#endif
