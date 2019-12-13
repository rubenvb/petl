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

#include "petl/utility/tuple_test_types.h++"

#include <petl/utility/as_tuple.h++>

using petl::as_tuple;

static_assert(std::is_same_v<decltype(as_tuple(bare)), std::tuple<int>>);
static_assert(std::is_same_v<decltype(as_tuple(bare_ref)), std::tuple<int>>);

static_assert(std::is_same_v<decltype(as_tuple(single)), std::tuple<int>>);
static_assert(std::is_same_v<decltype(as_tuple(nested_simple)), std::tuple<std::tuple<int>>>);

static_assert(std::is_same_v<decltype(as_tuple(multiple)), std::tuple<int, int>>);
static_assert(std::is_same_v<decltype(as_tuple(nested_multiple)), std::tuple<std::tuple<int, int>>>);

static_assert(std::is_same_v<decltype(as_tuple(multiply_nested)), std::tuple<std::tuple<int, int>, std::tuple<int, int>>>);
