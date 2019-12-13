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

#include <petl/expression/basic/double.h++>
#include <petl/expression/basic/int.h++>
#include <petl/expression/basic/literal.h++>

#include <petl/expression/sequence.h++>

using namespace petl;

using petl::expression::sequence;

// Sequence operator>>
constexpr auto literal = lit("dummy");
using literal_type = std::remove_const_t<decltype(literal)>;
using simple_sequence = decltype(int_ >> literal);
using left_sequence = decltype(simple_sequence{} >> double_);
using right_sequence = decltype(double_ >> simple_sequence{});
using triple_sequence = decltype(int_ >> double_ >> literal);

static_assert(std::is_same_v<simple_sequence,
                             sequence<expression::int_,
                                      literal_type>>);
static_assert(std::is_same_v<left_sequence,
                             sequence<expression::int_,
                                      literal_type,
                                      expression::double_>>);
static_assert(std::is_same_v<right_sequence,
                             sequence<expression::double_,
                                      expression::int_,
                                      literal_type>>);
static_assert(std::is_same_v<triple_sequence,
                             sequence<expression::int_,
                                      expression::double_,
                                      literal_type>>);

// Attributes
static_assert(std::is_same_v<attribute_of_t<simple_sequence>,
                             std::tuple<int>>);
static_assert(std::is_same_v<attribute_of_t<left_sequence>,
                             std::tuple<int, double>>);
static_assert(std::is_same_v<attribute_of_t<right_sequence>,
                             std::tuple<double, int>>);
static_assert(std::is_same_v<attribute_of_t<triple_sequence>,
                             std::tuple<int, double>>);
