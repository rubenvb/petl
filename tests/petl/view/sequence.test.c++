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

#include "../test.h++"

#include <petl/view/sequence.h++>

#include <iostream>
#include <string>

namespace
{
  struct A
  {
    int integer;
    std::string string;
  };

  using A_sequence = petl::view::sequence<&A::integer, &A::string>;
}

int main()
{
  using petl::test::check;

  A a{42, "42"};
  A_sequence sequence(a);

  check(petl::view::get<0>(sequence) == 42);
  check(petl::view::get<1>(sequence) == std::string{"42"});

  petl::view::get<0>(sequence) = 43;
  petl::view::get<1>(sequence) = "43";

  check(petl::view::get<0>(sequence) == 43);
  check(petl::view::get<1>(sequence) == std::string{"43"});

  return petl::test::exit_code;
}
